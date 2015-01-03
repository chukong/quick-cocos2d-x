#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pomelo-private/transport.h"
#include "pomelo-protocol/package.h"

void pc__tcp_close_cb(uv_handle_t *handler) {
  pc_transport_t *transport = (pc_transport_t *)handler->data;
  free(handler);
  free(transport);
}

pc_transport_t *pc_transport_new(pc_client_t *client) {
  pc_transport_t *transport = (pc_transport_t *)malloc(sizeof(pc_transport_t));

  if(transport == NULL) {
    fprintf(stderr, "Fail to malloc for pc_transport_t.\n");
    goto error;
  }

  memset(transport, 0, sizeof(pc_transport_t));

  transport->client = client;
  transport->socket = (uv_tcp_t *)malloc(sizeof(uv_tcp_t));
  if(transport->socket == NULL) {
    fprintf(stderr, "Fail to malloc for uv_tcp_t.\n");
    goto error;
  }

  if(uv_tcp_init(client->uv_loop, transport->socket)) {
    fprintf(stderr, "Fail to uv_tcp_init.\n");
    goto error;
  }

  transport->socket->data = transport;
  transport->state = PC_TP_ST_INITED;

  return transport;

error:
  if(transport->socket) free(transport->socket);
  if(transport) free(transport);

  return NULL;
}

void pc_transport_destroy(pc_transport_t *transport) {
  if(PC_TP_ST_CLOSED == transport->state) {
    return;
  }
  if(PC_TP_ST_INITED == transport->state) {
    free(transport);
    return;
  }

  transport->state = PC_TP_ST_CLOSED;
  uv_close((uv_handle_t *)transport->socket, pc__tcp_close_cb);
}

int pc_transport_start(pc_transport_t *transport) {
  if(PC_TP_ST_CONNECTING != transport->state) {
    fprintf(stderr, "Fail to start transport for invalid state: %d.\n",
            transport->state);
    return -1;
  }

  transport->state = PC_TP_ST_WORKING;

  return 0;
}

void pc_client_on_tcp_read(pc_client_t *client, const char *data, size_t len) {
  if(pc_pkg_parser_feed(client->pkg_parser, data, len)) {
    fprintf(stderr, "Fail to process data from server.\n");
    pc_client_stop(client);
  }
}

/**
 * Tcp data reached callback.
 */
void pc_tp_on_tcp_read(uv_stream_t *socket, ssize_t nread, uv_buf_t buf) {
  pc_transport_t *transport = (pc_transport_t *)socket->data;
  if(PC_TP_ST_WORKING != transport->state) {
    fprintf(stderr, "Discard read data for transport has stop work: %d\n",
            transport->state);
    goto error;
  }

  if (nread == -1) {
    if (uv_last_error(socket->loop).code != UV_EOF)
      fprintf(stderr, "Read error %s\n",
              uv_err_name(uv_last_error(transport->client->uv_loop)));
    transport->client->reconnecting = 0;
    pc_client_stop(transport->client);
    goto error;
  }

  if(nread == 0) {
    // read noting
    free(buf.base);
    return;
  }

  pc_client_on_tcp_read(transport->client, buf.base, nread);

error:
  if(buf.len != -1) {
    free(buf.base);
  }
}
