#include "pomelo.h"
#include "pomelo-protocol/package.h"

/**
 * Pomelo package heartbeat parsing and processing.
 */

int pc__binary_write(pc_client_t *client, const char *data, size_t len,
                            uv_write_cb cb);

static void pc__heartbeat_req_cb(uv_write_t* req, int status);

int pc__heartbeat(pc_client_t *client) {
  uv_timer_stop(client->timeout_timer);
  uv_timer_again(client->heartbeat_timer);
  return 0;
}

int pc__heartbeat_req(pc_client_t *client) {
  if(PC_ST_WORKING != client->state) {
    return -1;
  }

  pc_buf_t buf = pc_pkg_encode(PC_PKG_HEARBEAT, NULL, 0);
  if(buf.len == -1) {
    fprintf(stderr, "Fail to encode heartbeat package.\n");
    goto error;
  }

  if(pc__binary_write(client, buf.base, buf.len, pc__heartbeat_req_cb)) {
    fprintf(stderr, "Fail to send heartbeat request.\n");
    goto error;
  }

  return 0;

error:
  if(buf.len != -1) free(buf.base);
  return -1;
}

void pc__heartbeat_cb(uv_timer_t* heartbeat_timer, int status) {
  uv_timer_stop(heartbeat_timer);
  pc_client_t *client = (pc_client_t *)heartbeat_timer->data;
  if(status == -1) {
    fprintf(stderr, "Pomelo heartbeat timer error, %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    pc_client_stop(client);
    return;
  }

  if(pc__heartbeat_req(client)) {
    pc_client_stop(client);
    return;
  }

  uv_timer_again(client->timeout_timer);
}

void pc__timeout_cb(uv_timer_t* timeout_timer, int status) {
  uv_timer_stop(timeout_timer);
  pc_client_t *client = (pc_client_t *)timeout_timer->data;
  if(status == -1) {
    fprintf(stderr, "Pomelo timeout timer error, %s\n",
            uv_err_name(uv_last_error(client->uv_loop)));
  } else {
    pc_emit_event(client, PC_EVENT_TIMEOUT, NULL);
    fprintf(stderr, "Pomelo client heartbeat timeout.\n");
  }
  pc_client_stop(client);
}

static void pc__heartbeat_req_cb(uv_write_t* req, int status) {
  void **data = (void **)req->data;
  pc_client_t *client = (pc_client_t *)data[0];
  char *base = (char *)data[1];

  free(base);
  free(data);
  free(req);

  if(status == -1) {
    fprintf(stderr, "Fail to write heartbeat async, %s.\n",
            uv_err_name(uv_last_error(client->uv_loop)));
    pc_client_stop(client);
  }
}
