#include <string.h>
#include "pomelo.h"
#include "pomelo-private/internal.h"
#include "pomelo-protocol/message.h"
#include "pomelo-private/jansson-memory.h"

/**
 * Default implementation of Pomelo protocol encode and decode.
 */

static void pc__process_response(pc_client_t *client, pc_msg_t *msg) {
  char req_id_str[64];
  memset(req_id_str, 0, 64);
  sprintf(req_id_str, "%u", msg->id);

  pc_request_t *req = (pc_request_t *)pc_map_get(client->requests, req_id_str);
  if(req == NULL) {
    fprintf(stderr, "Fail to get pc_request_t for request id: %u.\n", msg->id);
    return;
  }

  // clean request for the reqId
  pc_map_del(client->requests, req_id_str);

  req->cb(req, 0, msg->msg);
}

static int pc__data(pc_client_t *client, const char *data, size_t len) {
  pc_msg_t *msg = client->parse_msg(client, data, len);

  if(msg == NULL) {
    return -1;
  }

  if(msg->id > 0) {
    pc__process_response(client, msg);
  } else {
    // server push message
    pc_emit_event(client, msg->route, msg->msg);
  }

  client->parse_msg_done(client, msg);

  return 0;
}

/**
 * New Pomelo package arrived callback.
 *
 * @param type   Pomelo package type
 * @param data   package body
 * @param len    package body length
 * @param attach attach pointer pass to pc_pkg_parser_t
 */
void pc__pkg_cb(pc_pkg_type type, const char *data, size_t len, void *attach) {
  pc_client_t *client = (pc_client_t *)attach;
  int status = 0;
  switch(type) {
    case PC_PKG_HANDSHAKE:
      status = pc__handshake_resp(client, data, len);
    break;
    case PC_PKG_HEARBEAT:
      status = pc__heartbeat(client);
    break;
    case PC_PKG_DATA:
      status = pc__data(client, data, len);
    break;
    case PC_PKG_KICK:
      pc_emit_event(client, PC_EVENT_KICK, NULL);
    break;
    default:
      fprintf(stderr, "Unknown Pomelo package type: %d.\n", type);
      status = -1;
    break;
  }

  if(status == -1) {
    pc_client_stop(client);
  }
}

const char *pc__resolve_dictionary(pc_client_t *client,
                                                 uint16_t code) {
  char code_str[16];
  memset(code_str, 0, 16);
  sprintf(code_str, "%u", code & 0xff);
  return json_string_value(json_object_get(client->code_to_route, code_str));
}

pc_msg_t *pc__default_msg_parse_cb(pc_client_t *client, const char *data,
    size_t len) {
  const char *route_str = NULL;
  pc_msg_t *msg = NULL;

  pc__msg_raw_t *raw_msg = pc_msg_decode(data, len);
  if(raw_msg == NULL) {
    goto error;
  }

  msg = (pc_msg_t *)malloc(sizeof(pc_msg_t));
  if(msg == NULL) {
    fprintf(stderr, "Fail to malloc for pc_msg_t while parsing raw message.\n");
    goto error;
  }
  memset(msg, 0, sizeof(pc_msg_t));

  msg->id = raw_msg->id;

  // route
  if(PC_MSG_HAS_ROUTE(raw_msg->type)) {
    const char *origin_route = NULL;
    // uncompress route dictionary
    if(raw_msg->compressRoute) {
      origin_route = pc__resolve_dictionary(client, raw_msg->route.route_code);
      if(origin_route == NULL) {
        fprintf(stderr, "Fail to uncompress route dictionary: %d.\n",
                raw_msg->route.route_code);
        goto error;
      }
    } else {
      origin_route = raw_msg->route.route_str;
    }

    route_str = (char *)malloc(strlen(origin_route) + 1);
    if(route_str == NULL) {
      fprintf(stderr, "Fail to malloc for uncompress route dictionary.\n");
      goto error;
    }

    memcpy((void *)route_str, (void *)origin_route, strlen(origin_route) + 1);
    msg->route = route_str;
  } else {
    // must be response, then get the route from requests map
    char id_str[64];
    memset(id_str, 0, 64);
    sprintf(id_str, "%u", msg->id);
    pc_request_t *req = (pc_request_t *)pc_map_get(client->requests, id_str);
    if(req == NULL) {
      fprintf(stderr, "Fail to get correlative request for the response: %u\n",
              msg->id);
      goto error;
    }
    route_str = req->route;
  }

  pc_buf_t body = raw_msg->body;
  if(body.len > 0) {
    json_t *pb_def = json_object_get(client->server_protos, route_str);
    if(pb_def) {
      // protobuf decode
      msg->msg = pc__pb_decode(body.base, 0, body.len, client->server_protos, pb_def);
    } else {
      // json decode
      msg->msg = pc__json_decode(body.base, 0, body.len);
    }

    if(msg->msg == NULL) {
      goto error;
    }
  }

  // release resources nolong used
  pc__raw_msg_destroy(raw_msg);

  return msg;

error:
  if(msg == NULL && route_str) free((void *)route_str);
  if(raw_msg) pc__raw_msg_destroy(raw_msg);
  if(msg) pc_msg_destroy(msg);
  return NULL;
}

void pc__default_msg_parse_done_cb(pc_client_t *client, pc_msg_t *msg) {
  if(msg != NULL) {
    pc_msg_destroy(msg);
  }
}

pc_buf_t pc__default_msg_encode_cb(pc_client_t *client, uint32_t reqId,
                                   const char *route, json_t *msg) {
  pc_buf_t msg_buf;
  pc_buf_t body_buf;

  msg_buf.base = NULL;
  body_buf.base = NULL;

  msg_buf.len = -1;
  body_buf.len = -1;

  // route encode
  int route_code = 0;
  json_t *code = json_object_get(client->route_to_code, route);
  if(code) {
    // dictionary compress
    route_code = json_integer_value(code);
  }

  // encode body
  json_t *pb_def = json_object_get(client->client_protos, route);
  if(pb_def) {
    body_buf = pc__pb_encode(msg, client->client_protos, pb_def);
    if(body_buf.len == -1) {
      fprintf(stderr, "Fail to encode message with protobuf: %s\n", route);
      goto error;
    }
  } else {
    // json encode
    body_buf = pc__json_encode(msg);
    if(body_buf.len == -1) {
      fprintf(stderr, "Fail to encode message with json: %s\n", route);
      goto error;
    }
  }

  // message type
  pc_msg_type type = PC_MSG_REQUEST;
  if(reqId == 0) {
    type = PC_MSG_NOTIFY;
  }

  if(route_code > 0) {
    msg_buf = pc_msg_encode_code(reqId, type, route_code, body_buf);
    if(msg_buf.len == -1) {
      fprintf(stderr, "Fail to encode message with route code: %d\n",
              route_code);
      goto error;
    }
  } else {
    msg_buf = pc_msg_encode_route(reqId, type, route, body_buf);
    if(msg_buf.len == -1) {
      fprintf(stderr, "Fail to encode message with route string: %s\n",
              route);
      goto error;
    }
  }

  if(body_buf.len != -1) {
    pc_jsonp_free(body_buf.base);
  }

  return msg_buf;

error:
  if(msg_buf.len != -1) free(msg_buf.base);
  if(body_buf.len != -1) pc_jsonp_free(body_buf.base);
  msg_buf.len = -1;
  msg_buf.base = NULL;
  return msg_buf;
}

void pc__default_msg_encode_done_cb(pc_client_t *client, pc_buf_t buf) {
  if(buf.len > 0) {
    free(buf.base);
  }
}

