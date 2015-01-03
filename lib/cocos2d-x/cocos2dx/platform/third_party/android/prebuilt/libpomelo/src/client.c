#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include "pomelo.h"
#include "pomelo-private/listener.h"
#include "pomelo-protocol/package.h"
#include "pomelo-protocol/message.h"
#include "pomelo-private/transport.h"
#include "pomelo-private/internal.h"
#include "pomelo-private/common.h"
#include "pomelo-private/ngx-queue.h"

static void pc__client_init(pc_client_t *client);
static void pc__close_async_cb(uv_async_t *handle, int status);
static void pc__release_listeners(pc_map_t *map, const char* key, void *value);
static void pc__release_requests(pc_map_t *map, const char* key, void *value);
static void pc__client_reconnect_reset(pc_client_t *client);
static void pc__client_reconnect_timer_cb(uv_timer_t* timer, int status);
static void pc__client_reconnect(pc_client_t *client);

pc_client_t *pc_client_new() {
  pc_client_t *client = (pc_client_t *)malloc(sizeof(pc_client_t));

  if(!client) {
    fprintf(stderr, "Fail to malloc for pc_client_t.\n");
    abort();
  }

  memset(client, 0, sizeof(pc_client_t));

  client->uv_loop = uv_loop_new();
  if(client->uv_loop == NULL) {
    fprintf(stderr, "Fail to create uv_loop_t.\n");
    abort();
  }

  pc__client_init(client);

  return client;
}

pc_client_t *pc_client_new_with_reconnect(int delay, int delay_max, int exp_backoff) {
  pc_client_t* client = pc_client_new();
  assert(client);
  if (delay <= 0 || delay_max <= 0) {
    fprintf(stderr, "Bad arguments, delay: %d, delay_max: %d", delay, delay_max);
    pc_client_destroy(client);
    return NULL;
  }

  client->enable_reconnect = 1;
  client->reconnect_delay = delay;
  client->reconnect_delay_max = delay_max;
  client->enable_exp_backoff = exp_backoff ? 1 : 0; 

  srand(time(0));

  if(!client->enable_exp_backoff){
    client->max_reconnects_incr = client->reconnect_delay_max / client->reconnect_delay + 1;
  } else {
    client->max_reconnects_incr = (int)log(1.0 * client->reconnect_delay_max / client->reconnect_delay) / log(2.0) + 1;
  }
  /* uv_timer_init never fail */
  uv_timer_init(client->uv_loop, &client->reconnect_timer); 

  return client;
}

/**
 * disconnect will make the uv loop to exit
 */
void pc_client_disconnect(pc_client_t* client){
  assert(client);
  uv_mutex_lock(&client->state_mutex);
  client->state = PC_ST_DISCONNECTING;
  uv_mutex_unlock(&client->state_mutex);
  uv_async_send(client->close_async);
}

void pc__client_init(pc_client_t *client) {
  client->listeners = pc_map_new(256, pc__release_listeners);
  if(client->listeners == NULL) {
    fprintf(stderr, "Fail to init client->listeners.\n");
    abort();
  }

  client->requests = pc_map_new(256, pc__release_requests);
  if(client->requests == NULL) {
    fprintf(stderr, "Fail to init client->requests.\n");
    abort();
  }

  client->pkg_parser = pc_pkg_parser_new(pc__pkg_cb, client);
  if(client->pkg_parser == NULL) {
    fprintf(stderr, "Fail to init client->pkg_parser.\n");
    abort();
  }

  client->heartbeat_timer = (uv_timer_t *)malloc(sizeof(uv_timer_t));
  if(client->heartbeat_timer == NULL) {
    fprintf(stderr, "Fail to malloc client->heartbeat_timer.\n");
    abort();
  }
  if(uv_timer_init(client->uv_loop, client->heartbeat_timer)) {
    fprintf(stderr, "Fail to init client->heartbeat_timer.\n");
    abort();
  }
  client->heartbeat_timer->timer_cb = pc__heartbeat_cb;
  client->heartbeat_timer->data = client;
  client->heartbeat = 0;

  client->timeout_timer = (uv_timer_t *)malloc(sizeof(uv_timer_t));
  if(client->timeout_timer == NULL) {
    fprintf(stderr, "Fail to malloc client->timeout_timer.\n");
    abort();
  }
  if(uv_timer_init(client->uv_loop, client->timeout_timer)) {
    fprintf(stderr, "Fail to init client->timeout_timer.\n");
    abort();
  }
  client->timeout_timer->timer_cb = pc__timeout_cb;
  client->timeout_timer->data = client;
  client->timeout = 0;

  client->close_async = (uv_async_t *)malloc(sizeof(uv_async_t));
  uv_async_init(client->uv_loop, client->close_async, pc__close_async_cb);
  client->close_async->data = client;
  uv_mutex_init(&client->mutex);
  uv_cond_init(&client->cond);
  uv_mutex_init(&client->listener_mutex);
  uv_mutex_init(&client->state_mutex);

  // init package parser
  client->parse_msg = pc__default_msg_parse_cb;
  client->parse_msg_done = pc__default_msg_parse_done_cb;

  // init package encoder
  client->encode_msg = pc__default_msg_encode_cb;
  client->encode_msg_done = pc__default_msg_encode_done_cb;

  client->state = PC_ST_INITED;
}

/**
 * as the state of pomelo client will be written by different thread, 
 * so it is necessary to protect it by a mutex.
 */
pc_client_state pc_client_get_state(pc_client_t *client) {
  pc_client_state state;
  uv_mutex_lock(&client->state_mutex);
  state = client->state;
  uv_mutex_unlock(&client->state_mutex);
  return state;
}
  
/**
 * Clear all inner resource of Pomelo client
 */
void pc__client_clear(pc_client_t *client) {
  if(client->listeners) {
    pc_map_destroy(client->listeners);
    client->listeners = NULL;
  }

  if(client->requests) {
    pc_map_destroy(client->requests);
    client->requests = NULL;
  }

  if(client->pkg_parser) {
    pc_pkg_parser_destroy(client->pkg_parser);
    client->pkg_parser = NULL;
  }

  if(client->handshake_opts) {
    json_decref(client->handshake_opts);
    client->handshake_opts = NULL;
  }

  if(client->route_to_code) {
    json_decref(client->route_to_code);
    client->route_to_code = NULL;
  }
  if(client->code_to_route) {
    json_decref(client->code_to_route);
    client->code_to_route = NULL;
  }
  if(client->server_protos) {
    json_decref(client->server_protos);
    client->server_protos = NULL;
  }
  if(client->client_protos) {
    json_decref(client->client_protos);
    client->client_protos = NULL;
  }
  if(client->proto_ver) {
    json_decref(client->proto_ver);
    client->proto_ver = NULL;
  }
}

void pc__client_reconnect_reset(pc_client_t *client) {
  assert(client);
  if(client->transport) {
    pc_transport_destroy(client->transport);
    client->transport = NULL;
  }

  if(client->heartbeat_timer != NULL) {
    uv_timer_stop(client->heartbeat_timer);
    client->heartbeat = 0;
  }

  if(client->timeout_timer != NULL) {
    uv_timer_stop(client->timeout_timer);
    client->timeout = 0;
  } 
  
  if(client->requests) {
    pc_map_clear(client->requests);
  }

  if(client->pkg_parser) {
    pc_pkg_parser_reset(client->pkg_parser);
  }

  if(client->handshake_opts) {
    json_decref(client->handshake_opts);
    client->handshake_opts = NULL;
  }

  if(client->route_to_code) {
    json_decref(client->route_to_code);
    client->route_to_code = NULL;
  }
  if(client->code_to_route) {
    json_decref(client->code_to_route);
    client->code_to_route = NULL;
  }
  if(client->server_protos) {
    json_decref(client->server_protos);
    client->server_protos = NULL;
  }
  if(client->client_protos) {
    json_decref(client->client_protos);
    client->client_protos = NULL;
  }
  uv_mutex_lock(&client->state_mutex);
  client->state = PC_ST_INITED;
  uv_mutex_unlock(&client->state_mutex);
}

void pc_client_stop(pc_client_t *client) {
  pc_client_state state;
  uv_mutex_lock(&client->state_mutex);
  state = client->state;
  uv_mutex_unlock(&client->state_mutex);

  if (client->enable_reconnect && state != PC_ST_DISCONNECTING) {
    // still reconnecting, just return
    if (client->reconnecting){
      return;
    }

    pc_emit_event(client, PC_EVENT_DISCONNECT, NULL);
    pc__client_reconnect(client);
    return;
  }

  if(PC_ST_INITED == state) {
    client->state = PC_ST_CLOSED;
    return;
  }

  if(PC_ST_CLOSED == state) {
    return;
  }

  uv_mutex_lock(&client->state_mutex);
  client->state = PC_ST_CLOSED;
  uv_mutex_unlock(&client->state_mutex);

  if(client->transport) {
    pc_transport_destroy(client->transport);
    client->transport = NULL;
  }

  if(client->heartbeat_timer != NULL) {
    uv_close((uv_handle_t *)client->heartbeat_timer, pc__handle_close_cb);
    client->heartbeat_timer = NULL;
    client->heartbeat = 0;
  }
  if(client->timeout_timer != NULL) {
    uv_close((uv_handle_t *)client->timeout_timer, pc__handle_close_cb);
    client->timeout_timer = NULL;
    client->timeout = 0;
  }
  if(client->close_async != NULL) {
    uv_close((uv_handle_t *)client->close_async, pc__handle_close_cb);
    client->close_async = NULL;
  }

  if(client->enable_reconnect) {
    uv_close((uv_handle_t*)&client->reconnect_timer, NULL);
  }
}

void pc__client_reconnect(pc_client_t *client) {
  client->reconnecting = 1;
  client->reconnect_timer.data = client;
  pc__client_reconnect_reset(client);
  client->reconnects++;
  int delay = 0;
  if (client->reconnects >= client->max_reconnects_incr) {
    delay = client->reconnect_delay_max;
  } else {
    if (client->enable_exp_backoff) {
      delay = client->reconnect_delay << client->reconnects;
    } else {
      delay = client->reconnect_delay * client->reconnects;
    }
  }

  if (delay > client->reconnect_delay_max) delay = client->reconnect_delay_max;

  delay = rand() % delay + delay;

  fprintf(stderr, "reconnect: %d, delay: %d\n", client->reconnects, delay);
  uv_timer_start(&client->reconnect_timer, pc__client_reconnect_timer_cb, delay * 1000, 0);
}

void pc__client_reconnected_cb(pc_connect_t* conn_req, int status) {
  pc_client_t* client = conn_req->client;
  client->reconnecting = 0;
  uv_timer_stop(&client->reconnect_timer);
  if (status == 0) {
    client->reconnects = 0;
    pc_emit_event(client, PC_EVENT_RECONNECT, client);
  } else {
    pc_client_stop(client);
  }
}

void pc__client_reconnect_timer_cb(uv_timer_t* timer, int status) {
  /* unused */
  (void)status;
  pc_client_t* client = (pc_client_t*)timer->data;
  pc_connect_t* conn_req = pc_connect_req_new(&client->addr);
  if (!conn_req) {
    fprintf(stderr, "out of memory");
    pc_client_stop(client);
  }

  if(pc_connect(client, conn_req, NULL, pc__client_reconnected_cb)) {
    fprintf(stderr, "Fail to connect to server.\n");
    pc_connect_req_destroy(conn_req);
    client->reconnecting = 0;
    pc_client_stop(client);
  }
}

void pc_client_destroy(pc_client_t *client) {
  pc_client_state state;

  uv_mutex_lock(&client->state_mutex);
  state = client->state;
  uv_mutex_unlock(&client->state_mutex);

  if(PC_ST_INITED == client->state) {
    goto finally;
  }

  if(PC_ST_CLOSED == client->state) {
    goto finally;
  }

  pc_client_disconnect(client);
  pc_client_join(client);

finally:
  pc__client_clear(client);

  if(client->uv_loop) {
    uv_loop_delete(client->uv_loop);
    client->uv_loop = NULL;
  }
  free(client);
}

int pc_client_join(pc_client_t *client) {
  return uv_thread_join(&client->worker);
}

int pc_client_connect(pc_client_t *client, struct sockaddr_in *addr) {
  pc_connect_t *conn_req = pc_connect_req_new(addr);

  if(client->enable_reconnect){
    memcpy(&client->addr, addr, sizeof(struct sockaddr_in));
  }

  if(conn_req == NULL) {
    fprintf(stderr, "Fail to malloc pc_connect_t.\n");
    goto error;
  }

  if(pc_connect(client, conn_req, NULL, pc__client_connected_cb)) {
    fprintf(stderr, "Fail to connect to server.\n");
    goto error;
  }

  // 1. start work thread
  // 2. wait connect result

  uv_thread_create(&client->worker, pc__worker, client);

  // TODO should set a timeout?
  pc__cond_wait(client, 0);

  pc_connect_req_destroy(conn_req);

  if(PC_ST_WORKING != client->state) {
    return -1;
  }

  return 0;
error:
  if(conn_req) pc_connect_req_destroy(conn_req);
  return -1;
}

int pc_client_connect2(pc_client_t *client, pc_connect_t *conn_req, pc_connect_cb cb){
  if(client->enable_reconnect){
    memcpy(&client->addr, conn_req->address, sizeof(struct sockaddr_in));
  }

  if(pc_connect(client, conn_req, NULL, cb)){
    // When failed, user should be responsible of reclaiming conn_req's memory
	// When succeeded, user should be responsible of reclaiming con_req's memory in cb
	// This API do not hold any assumption of conn_req(How it resides in memory)
    fprintf(stderr,"Fail to connect server.\n");
	return -1;
  }
  
  uv_thread_create(&client->worker, pc__worker, client);
  return 0;
}

static void pc__client_connect3_cb(pc_connect_t* req, int status) {
  if(status == -1) {
    pc_client_stop(req->client);
    pc_connect_req_destroy(req);
    return;
  }

  pc_emit_event(req->client, PC_EVENT_RECONNECT, req->client);
  pc_connect_req_destroy(req);
}

int pc_client_connect3(pc_client_t *client, struct sockaddr_in *addr) {
  pc_connect_t *conn_req = pc_connect_req_new(addr);

  if(client->enable_reconnect){
    memcpy(&client->addr, addr, sizeof(struct sockaddr_in));
  }

  if(conn_req == NULL) {
    fprintf(stderr, "Fail to malloc pc_connect_t.\n");
    goto error;
  }

  if(pc_connect(client, conn_req, NULL, pc__client_connect3_cb)) {
    fprintf(stderr, "Fail to connect to server.\n");
    goto error;
  }

  uv_thread_create(&client->worker, pc__worker, client);

  return 0;

error:
  if(conn_req) pc_connect_req_destroy(conn_req);
  return -1;
}


int pc_add_listener(pc_client_t *client, const char *event,
                    pc_event_cb event_cb) {
  if(PC_ST_CLOSED == client->state) {
    fprintf(stderr, "Pomelo client has closed.\n");
    return -1;
  }

  pc_listener_t *listener = pc_listener_new();
  if(listener == NULL) {
    fprintf(stderr, "Fail to create listener.\n");
    return -1;
  }
  listener->cb = event_cb;

  uv_mutex_lock(&client->listener_mutex);
  ngx_queue_t *head = (ngx_queue_t *)pc_map_get(client->listeners, event);

  if(head == NULL) {
    head = (ngx_queue_t *)malloc(sizeof(ngx_queue_t));
    if(head == NULL) {
      fprintf(stderr, "Fail to create listener queue.\n");
      pc_listener_destroy(listener);
      uv_mutex_unlock(&client->listener_mutex);
      return -1;
    }

    ngx_queue_init(head);

    pc_map_set(client->listeners, event, head);
  }

  ngx_queue_insert_tail(head, &listener->queue);
  uv_mutex_unlock(&client->listener_mutex);

  return 0;
}

void pc_remove_listener(pc_client_t *client, const char *event, pc_event_cb cb) {
  uv_mutex_lock(&client->listener_mutex);
  ngx_queue_t *head = (ngx_queue_t *)pc_map_get(client->listeners, event);
  if(head == NULL) {
    uv_mutex_unlock(&client->listener_mutex);
    return;
  }

  ngx_queue_t *item = NULL;
  pc_listener_t *listener = NULL;

  ngx_queue_foreach(item, head) {
    listener = ngx_queue_data(item, pc_listener_t, queue);
    if(listener->cb == cb) {
      ngx_queue_remove(item);
      pc_listener_destroy(listener);
      break;
    }
  }

  if(ngx_queue_empty(head)) {
    pc_map_del(client->listeners, event);
    free(head);
  }
  uv_mutex_unlock(&client->listener_mutex);
}

void pc_emit_event(pc_client_t *client, const char *event, void *data) {
  uv_mutex_lock(&client->listener_mutex);
  ngx_queue_t *head = (ngx_queue_t *)pc_map_get(client->listeners, event);
  if(head == NULL) {
    uv_mutex_unlock(&client->listener_mutex);
    return;
  }

  ngx_queue_t *item = NULL;
  pc_listener_t *listener = NULL;

  ngx_queue_foreach(item, head) {
    listener = ngx_queue_data(item, pc_listener_t, queue);
    listener->cb(client, event, data);
  }
  uv_mutex_unlock(&client->listener_mutex);
}

int pc_run(pc_client_t *client) {
  if(!client || !client->uv_loop) {
    fprintf(stderr, "Invalid client to run.\n");
    return -1;
  }
  return uv_run(client->uv_loop, UV_RUN_DEFAULT);
};

void pc__release_listeners(pc_map_t *map, const char* key, void *value) {
  if(value == NULL) {
    return;
  }

  ngx_queue_t *head = (ngx_queue_t *)value;
  ngx_queue_t *q;
  pc_listener_t *l;
  while (!ngx_queue_empty(head)) {
    q = ngx_queue_head(head);
    ngx_queue_remove(q);
    ngx_queue_init(q);

    l = ngx_queue_data(q, pc_listener_t, queue);
    pc_listener_destroy(l);
  }

  free(head);
}

void pc__release_requests(pc_map_t *map, const char* key, void *value) {
  if(value == NULL) {
    return;
  }

  pc_request_t *req = (pc_request_t *)value;
  req->cb(req, -1, NULL);
}

void pc__close_async_cb(uv_async_t *handle, int status) {
  pc_client_t *client = (pc_client_t *)handle->data;
  pc_client_stop(client);
}

void pc_proto_init(pc_client_t *client, const char *proto_read_dir, const char *proto_write_dir) {
  if(!client) {
    fprintf(stderr, "Fail to init protobuf, the client is null.\n");
    return;
  }
  client->proto_read_dir = proto_read_dir;
  client->proto_write_dir = proto_write_dir;
}

void pc_proto_init2(pc_client_t *client, pc_proto_cb proto_cb) {
  if(!client) {
    fprintf(stderr, "Fail to init protobuf, the client is null.\n");
    return;
  }
  client->proto_event_cb = proto_cb;
}

void pc_proto_copy(pc_client_t *client, json_t *proto_ver, json_t *client_protos, json_t *server_protos) {
  if (!client) {
    fprintf(stderr, "Fail to copy protobuf info, one client is null.\n");
    return;
  }
  client->proto_ver = proto_ver;
  client->client_protos = client_protos;
  client->server_protos = server_protos;
}
