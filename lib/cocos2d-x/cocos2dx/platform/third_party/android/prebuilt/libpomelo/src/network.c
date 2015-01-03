#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pomelo.h"
#include "pomelo-protocol/package.h"
#include "pomelo-protocol/message.h"
#include "pomelo-private/common.h"
#include "pomelo-private/transport.h"

int pc__handshake_req(pc_client_t *client);

// private callback functions
static uv_buf_t pc__alloc_buffer(uv_handle_t *handle, size_t suggested_size);
static void pc__on_tcp_read(uv_stream_t *handle, ssize_t nread, uv_buf_t buf);
static void pc__on_tcp_connect(uv_connect_t *req, int status);
static void pc__on_notify(uv_write_t* req, int status);
static void pc__on_request(uv_write_t *req, int status);
static int pc__async_write(pc_transport_t *transport, pc_tcp_req_t *req,
                           const char *route, json_t *msg);
static void pc__async_write_cb(uv_async_t* handle, int status);
static void pc__notify(pc_notify_t *req, int status);
static void pc__request(pc_request_t *req, int status);

static uint32_t pc__req_id = 0;

/**
 * Create and initiate connect request instance.
 */
pc_connect_t *pc_connect_req_new(struct sockaddr_in *address) {
  if(address == NULL) {
    fprintf(stderr, "Invalid address argument for pc_connect_req_init.\n");
    return NULL;
  }

  pc_connect_t *req = (pc_connect_t *)malloc(sizeof(pc_connect_t));
  if(req == NULL) {
    fprintf(stderr, "Fail to malloc for pc_connect_t.\n");
    return NULL;
  }

  memset(req, 0, sizeof(pc_connect_t));
  req->type = PC_CONNECT;

  struct sockaddr_in *cpy_addr =
      (struct sockaddr_in *)malloc(sizeof (struct sockaddr_in));

  if(cpy_addr == NULL) {
    fprintf(stderr, "Fail to malloc sockaddr_in in pc_connect_req_init.\n");
    goto error;
  }

  memcpy(cpy_addr, address, sizeof(struct sockaddr_in));
  req->address = cpy_addr;

  return req;

error:
  if(req) free(req);
  if(cpy_addr) free(cpy_addr);
  return NULL;
}

void pc_connect_req_destroy(pc_connect_t *req) {
  if(req->address) {
    free(req->address);
    req->address = NULL;
  }
  free(req);
}

/**
 * Connect the pomelo client to server.
 */
int pc_connect(pc_client_t *client, pc_connect_t *req,
               json_t *handshake_opts, pc_connect_cb cb) {
  if(client->state != PC_ST_INITED) {
    fprintf(stderr, "Invalid Pomelo client state: %d.\n", client->state);
    return -1;
  }

  if(!req || !req->address) {
    fprintf(stderr, "Invalid connect request.\n");
    return -1;
  }

  client->state = PC_ST_CONNECTING;

  uv_connect_t *connect_req = NULL;
  pc_transport_t *transport = NULL;
  void **data = NULL;

  connect_req = (uv_connect_t *)malloc(sizeof(uv_connect_t));
  if(connect_req == NULL) {
    fprintf(stderr, "Fail to malloc for uv_connect_t.\n");
    return -1;
  }

  data = (void **)malloc(sizeof(void *) * 2);

  if(data == NULL) {
    fprintf(stderr, "Fail to malloc for data array in pc_connect.\n");
    goto error;
  }

  transport = pc_transport_new(client);
  if(transport == NULL) {
    goto error;
  }

  client->handshake_opts = handshake_opts;
  if(client->handshake_opts) {
    json_incref(client->handshake_opts);
  }
  client->conn_req = req;
  req->client = client;
  req->transport = transport;
  req->cb = cb;
  data[0] = transport;
  data[1] = req;
  connect_req->data = (void *)data;

  if(uv_tcp_connect(connect_req, transport->socket,
                    *req->address, pc__on_tcp_connect)) {
    fprintf(stderr, "Fail to connect to server.");
    goto error;
  }
  transport->state = PC_TP_ST_CONNECTING;

  return 0;

error:
  req->data = NULL;
  if(data) free(data);
  if(transport) pc_transport_destroy(transport);
  if(connect_req) free(connect_req);

  return -1;
}

pc_request_t *pc_request_new() {
  pc_request_t *req = (pc_request_t *)malloc(sizeof(pc_request_t));
  if(req == NULL) {
    fprintf(stderr, "Fail to malloc for new pc_request_t.\n");
    return NULL;
  }

  memset(req, 0, sizeof(pc_request_t));
  req->type = PC_REQUEST;

  return req;
}

void pc_request_destroy(pc_request_t *req) {
  if(req->route) {
    free((void *)req->route);
    req->route = NULL;
  }
  free(req);
}

int pc_request(pc_client_t *client, pc_request_t *req, const char *route,
               json_t *msg, pc_request_cb cb) {
  if(PC_ST_WORKING != client->state) {
    fprintf(stderr, "Invalid client state to send request: %d\n", client->state);
    return -1;
  }
  req->cb = cb;
  req->id = ++pc__req_id;
  return pc__async_write(client->transport, (pc_tcp_req_t *)req, route, msg);
}

/**
 * Create and initiate notify request instance.
 */
pc_notify_t *pc_notify_new() {
  pc_notify_t *req = (pc_notify_t *)malloc(sizeof(pc_notify_t));
  if(req == NULL) {
    fprintf(stderr, "Fail to malloc new pc_notify_t.\n");
    return NULL;
  }
  memset(req, 0, sizeof(pc_notify_t));
  req->type = PC_NOTIFY;

  return req;
}

void pc_notify_destroy(pc_notify_t *req) {
  if(req->route) {
    free((void *)req->route);
    req->route = NULL;
  }
  free(req);
}

/**
 * Send notify to server.
 */
int pc_notify(pc_client_t *client, pc_notify_t *req, const char *route,
              json_t *msg, pc_notify_cb cb) {
  if(PC_ST_WORKING != client->state) {
    fprintf(stderr, "Invalid client state to send notify: %d\n", client->state);
    return -1;
  }

  req->cb = cb;
  return pc__async_write(client->transport, (pc_tcp_req_t *)req, route, msg);
}

static void pc__request(pc_request_t *req, int status) {
  if(status == -1) {
    req->cb(req, status, NULL);
    return;
  }

  pc_transport_t *transport = req->transport;

  // check transport state again
  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Fail to request for transport not working.\n");
    req->cb(req, status, NULL);
    return;
  }

  pc_client_t *client = transport->client;
  pc_buf_t msg_buf, pkg_buf;
  uv_write_t * write_req = NULL;
  void **data = NULL;

  memset(&msg_buf, 0, sizeof(pc_buf_t));
  memset(&pkg_buf, 0, sizeof(pc_buf_t));

  msg_buf = client->encode_msg(client, req->id, req->route, req->msg);

  if(msg_buf.len == -1) {
    fprintf(stderr, "Fail to encode request message.\n");
    goto error;
  }

  pkg_buf = pc_pkg_encode(PC_PKG_DATA, msg_buf.base, msg_buf.len);

  if(msg_buf.len == -1) {
    fprintf(stderr, "Fail to encode request package.\n");
    goto error;
  }

  write_req = (uv_write_t *)malloc(sizeof(uv_write_t));

  if(write_req == NULL) {
    goto error;
  }

  memset(write_req, 0, sizeof(uv_write_t));

  // record request context
  data = (void **)malloc(sizeof(void *) * 2);
  if(data == NULL) {
    fprintf(stderr, "Fail to malloc void** for pc__request.\n");
    goto error;
  }

  data[0] = (void *)req;
  data[1] = pkg_buf.base;
  write_req->data = (void *)data;

  int res = uv_write(write_req, (uv_stream_t *)client->transport->socket,
                     (uv_buf_t *)&pkg_buf, 1, pc__on_request);

  if(res == -1) {
    fprintf(stderr, "Send message error %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    goto error;
  }

  char req_id_str[64];
  memset(req_id_str, 0, 64);
  sprintf(req_id_str, "%u", req->id);
  pc_map_set(client->requests, req_id_str, req);

  client->encode_msg_done(client, msg_buf);

  return;

error:
  if(msg_buf.len != -1) free(msg_buf.base);
  if(pkg_buf.len != -1) free(pkg_buf.base);
  if(write_req) free(write_req);
  if(data) free(data);
  req->cb(req, -1, NULL);
}

/**
 * Async callback and send notify to server finally.
 */
static void pc__notify(pc_notify_t *req, int status) {
  if(status == -1) {
    req->cb(req, status);
    return;
  }

  pc_transport_t *transport = req->transport;

  // check client state again
  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Fail to notify for transport not working.\n");
    req->cb(req, status);
    return;
  }

  pc_client_t *client = transport->client;
  pc_buf_t msg_buf;
  pc_buf_t pkg_buf;
  memset(&msg_buf, 0, sizeof(pc_buf_t));
  memset(&pkg_buf, 0, sizeof(pc_buf_t));

  uv_write_t * write_req = NULL;
  void** data = NULL;

  msg_buf = client->encode_msg(client, 0, req->route, req->msg);

  if(msg_buf.len == -1) {
    fprintf(stderr, "Fail to encode request message.\n");
    goto error;
  }

  pkg_buf = pc_pkg_encode(PC_PKG_DATA, msg_buf.base, msg_buf.len);

  if(msg_buf.len == -1) {
    fprintf(stderr, "Fail to encode request package.\n");
    goto error;
  }

  write_req = (uv_write_t *)malloc(sizeof(uv_write_t));

  if(write_req == NULL) {
    goto error;
  }

  memset(write_req, 0, sizeof(uv_write_t));

  // record notify context
  data = (void **)malloc(sizeof(void *) * 2);
  if(data == NULL) {
    fprintf(stderr, "Fail to malloc void** for pc__request.\n");
    goto error;
  }

  data[0] = (void *)req;
  data[1] = pkg_buf.base;
  write_req->data = (void *)data;

  int res = uv_write(write_req, (uv_stream_t *)client->transport->socket,
                     (uv_buf_t *)&pkg_buf, 1, pc__on_notify);

  if(res == -1) {
    fprintf(stderr, "Send message error %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    goto error;
  }

  client->encode_msg_done(client, msg_buf);

  return;

error:
  if(msg_buf.len != -1) free(msg_buf.base);
  if(pkg_buf.len != -1) free(pkg_buf.base);
  if(write_req) free(write_req);
  if(data) free(data);
  req->cb(req, -1);
}

/**
 * Allocate buffer callback for uv_read_start.
 */
static uv_buf_t pc__alloc_buffer(uv_handle_t *handle, size_t suggested_size) {
  return uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

/**
 * Tcp connection established callback.
 */
static void pc__on_tcp_connect(uv_connect_t *req, int status) {
  void **data = (void **)req->data;
  pc_transport_t *transport = (pc_transport_t *)data[0];
  pc_connect_t *conn_req = (pc_connect_t *)data[1];
  pc_client_t *client = transport->client;

  free(req);
  free(data);

  if(PC_ST_CONNECTING != client->state) {
    fprintf(stderr, "Invalid client state when tcp connected: %d.\n",
            client->state);
    client->conn_req = NULL;
    conn_req->cb(conn_req, -1);
    return;
  }

  if(status == -1) {
    fprintf(stderr, "Connect failed error %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    pc_transport_destroy(transport);
    goto error;
  }

  client->transport = transport;

  // start the tcp reading until disconnect
  if(uv_read_start((uv_stream_t*)transport->socket, pc__alloc_buffer,
                   pc_tp_on_tcp_read)) {
    fprintf(stderr, "Fail to start reading server %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    goto error;
  }

  client->state = PC_ST_CONNECTED;
  pc_transport_start(transport);

  if(pc__handshake_req(client)) {
    goto error;
  }

  return;

error:
  client->conn_req = NULL;
  pc_client_stop(client);
  conn_req->cb(conn_req, -1);
}

// Async write for pc_notify or pc_request may be invoked in other threads.
static int pc__async_write(pc_transport_t *transport, pc_tcp_req_t *req,
                           const char *route, json_t *msg) {
  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Fail to asyn write for transport not working: %d.\n",
            transport->state);
    return -1;
  }

  if(!req || !route /*|| !msg*/) {
    fprintf(stderr, "Invalid tcp request.\n");
    return -1;
  }

  pc_client_t *client = transport->client;
  size_t route_len = strlen(route) + 1;
  const char *cpy_route = NULL;
  uv_async_t *async_req = NULL;
  req->route = NULL;

  cpy_route = (char *)malloc(route_len);
  if(cpy_route == NULL) {
    fprintf(stderr, "Fail to malloc for route string in pc__async_write.\n");
    goto error;
  }
  memcpy((void *)cpy_route, route, route_len);

  int async_inited = 0;
  req->client = client;
  req->transport = transport;
  req->route = cpy_route;
  req->msg = msg;

  async_req = (uv_async_t *)malloc(sizeof(uv_async_t));
  if(async_req == NULL) {
    fprintf(stderr, "Fail to malloc for async notify.\n");
    goto error;
  }

  if(uv_async_init(client->uv_loop, async_req, pc__async_write_cb)) {
    fprintf(stderr, "Fail to init async write tcp request, type: %d.\n",
            req->type);
    goto error;
  }

  async_inited = 1;

  async_req->data = (void *)req;
  if(uv_async_send(async_req)) {
    fprintf(stderr, "Fail to send async write tcp request, type: %d.\n",
            req->type);
    goto error;
  }

  return 0;

error:
  if(req->route) {
    free((void *)req->route);
    req->route = NULL;
  }
  if(async_inited) {
    // should not release the async_req before close callback
    uv_close((uv_handle_t *)async_req, pc__handle_close_cb);
  } else {
    if(async_req) free(async_req);
  }
  return -1;
}

static void pc__async_write_cb(uv_async_t* req, int status) {
  pc_tcp_req_t *tcp_req = (pc_tcp_req_t *)req->data;
  uv_close((uv_handle_t *)req, pc__handle_close_cb);
  if(tcp_req->type == PC_NOTIFY) {
    pc__notify((pc_notify_t *)tcp_req, status);
  } else if(tcp_req->type == PC_REQUEST) {
    pc__request((pc_request_t *)tcp_req, status);
  } else {
    fprintf(stderr, "Unknown tcp request type: %d\n", tcp_req->type);
    // TDOO: should abort? How to free unknown tcp request
    free(tcp_req);
    return;
  }
}

/**
 * Request callback.
 */
static void pc__on_request(uv_write_t *req, int status) {
  void **data = (void **)req->data;
  pc_request_t *request_req = (pc_request_t *)data[0];
  pc_transport_t *transport = request_req->transport;
  pc_client_t *client = transport->client;
  char *base = (char *)data[1];

  free(base);
  free(req);
  free(data);

  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Request error for transport not working.\n");
    request_req->cb(request_req, -1, NULL);
    return;
  }

  if(status == -1) {
    fprintf(stderr, "Request error %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    char req_id_str[64];
    memset(req_id_str, 0, 64);
    sprintf(req_id_str, "%u", request_req->id);

    // clean request map
    pc_map_del(client->requests, req_id_str);

    request_req->cb(request_req, status, NULL);
  }

}

/**
 * Notify callback.
 */
static void pc__on_notify(uv_write_t *req, int status) {
  void **data = (void **)req->data;
  pc_notify_t *notify_req = (pc_notify_t *)data[0];
  pc_transport_t *transport = notify_req->transport;
  pc_client_t *client = transport->client;
  char *base = (char *)data[1];

  free(base);
  free(req);
  free(data);

  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Notify error for transport not working.\n");
    notify_req->cb(notify_req, -1);
    return;
  }

  if(status == -1) {
    fprintf(stderr, "Notify error %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
  }

  notify_req->cb(notify_req, status);
}

int pc__binary_write(pc_client_t *client, const char *data, size_t len,
                            uv_write_cb cb) {
  if(PC_ST_CONNECTED != client->state && PC_ST_WORKING != client->state) {
    fprintf(stderr, "Fail to write binary for invalid client state: %d.\n",
            client->state);
    return -1;
  }

  uv_write_t *req = NULL;
  void **attach = NULL;

  req = (uv_write_t *)malloc(sizeof(uv_write_t));
  if(req == NULL) {
    fprintf(stderr, "Fail to malloc for uv_write_t.\n");
    goto error;
  }

  memset(req, 0, sizeof(uv_write_t));

  attach = (void **)malloc(sizeof(void *) * 2);
  if(data == NULL) {
    fprintf(stderr, "Fail to malloc data for handshake ack.\n");
    goto error;
  }

  attach[0] = client->transport;
  attach[1] = (void *)data;
  req->data = (void *)attach;

  uv_buf_t buf;
  buf.base = (char *)data;
  buf.len = len;

  if(uv_write(req, (uv_stream_t *)client->transport->socket, &buf, 1, cb)) {
    fprintf(stderr, "Fail to write handshake ack pakcage, %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    goto error;
  }

  return 0;
error:
  if(req) free(req);
  if(attach) free(attach);
  return -1;
}
