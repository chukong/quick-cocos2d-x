#include <assert.h>
#include <string.h>
#include "pomelo-protocol/message.h"

static uint8_t pc__msg_id_length(uint32_t id);

static inline size_t pc__msg_encode_flag(pc_msg_type type, int compressRoute,
                                         char *base, size_t offset);

static inline size_t pc__msg_encode_id(uint32_t id, char *base, size_t offset);

static inline size_t pc__msg_encode_route(const char *route, uint16_t route_len,
                                          char *base, size_t offset);

pc_buf_t pc_msg_encode_route(uint32_t id, pc_msg_type type,
                             const char *route, pc_buf_t msg) {
  pc_buf_t buf;

  memset(&buf, 0, sizeof(pc_buf_t));

  uint8_t id_len = PC_MSG_HAS_ID(type) ? pc__msg_id_length(id) : 0;
  uint16_t route_len = PC_MSG_HAS_ROUTE(type) ? strlen(route) : 0;

  size_t msg_len = PC_MSG_FLAG_BYTES + id_len + PC_MSG_ROUTE_LEN_BYTES +
                   route_len + msg.len;

  char *base = buf.base = (char *)malloc(msg_len);

  if(buf.base == NULL) {
    buf.len = -1;
    goto error;
  }

  size_t offset = 0;

  // flag
  offset = pc__msg_encode_flag(type, 0, base, offset);

  // message id
  if(PC_MSG_HAS_ID(type)) {
    offset = pc__msg_encode_id(id, base, offset);
  }

  // route
  if(PC_MSG_HAS_ROUTE(type)) {
    offset = pc__msg_encode_route(route, route_len, base, offset);
  }

  // body
  memcpy(base + offset, msg.base, msg.len);

  buf.len = msg_len;

  return buf;

error:
  if(buf.len != -1) free(buf.base);
  buf.len = -1;
  return buf;
}

pc_buf_t pc_msg_encode_code(uint32_t id, pc_msg_type type,
                            int routeCode, pc_buf_t msg) {
  pc_buf_t buf;

  memset(&buf, 0, sizeof(pc_buf_t));

  uint8_t id_len = PC_MSG_HAS_ID(type) ? pc__msg_id_length(id) : 0;
  uint16_t route_len = PC_MSG_HAS_ROUTE(type) ? PC_MSG_ROUTE_CODE_BYTES : 0;

  size_t msg_len = PC_MSG_FLAG_BYTES + id_len + route_len + msg.len;

  char *base = buf.base = (char *)malloc(msg_len);

  if(buf.base == NULL) {
    buf.len = -1;
    goto error;
  }

  size_t offset = 0;

  // flag
  offset = pc__msg_encode_flag(type, 1, base, offset);

  // message id
  if(PC_MSG_HAS_ID(type)) {
    offset = pc__msg_encode_id(id, base, offset);
  }

  // route code
  if(PC_MSG_HAS_ROUTE(type)) {
    base[offset++] = (routeCode >> 8) & 0xff;
    base[offset++] = routeCode & 0xff;
  }

  // body
  memcpy(base + offset, msg.base, msg.len);

  buf.len = msg_len;

  return buf;

error:
  if(buf.len != -1) free(buf.base);
  buf.len = -1;
  return buf;
}

pc__msg_raw_t *pc_msg_decode(const char *data, size_t len) {
  pc__msg_raw_t *msg = NULL;
  char *route_str = NULL;
  char *body = NULL;

  msg = (pc__msg_raw_t *)malloc(sizeof(pc__msg_raw_t));
  if(msg == NULL) {
    fprintf(stderr, "Fail to malloc for pc_raw_msg_t.\n");
    return NULL;
  }
  memset(msg, 0, sizeof(pc__msg_raw_t));

  size_t offset = 0;

  PC__MSG_CHECK_LEN(offset + PC_MSG_FLAG_BYTES, len);
  // flag
  uint8_t flag = data[offset++];

  // type
  uint8_t type = (flag >> 1) & 0xff;

  if(!PC_MSG_VALIDATE(type)) {
    fprintf(stderr, "Unknown Pomleo message type: %d.\n", type);
    goto error;
  }

  msg->type = (pc_msg_type)type;

  // compress flag
  uint8_t compressRoute = flag & 0x01;
  msg->compressRoute = compressRoute;

  // message id
  uint32_t id = 0;

  if(PC_MSG_HAS_ID(type)) {
    PC__MSG_CHECK_LEN(offset + 1, len);
    int i = 0;
    uint8_t m;
    do{
      m = data[offset++];
      id = id + ((m & 0x7f) * (1 << (7*i)));
      i++;
    }while(m >= 128);
  }
  msg->id = id;

  // route
  if(PC_MSG_HAS_ROUTE(type)) {
    if(compressRoute) {
      PC__MSG_CHECK_LEN(offset + PC_MSG_ROUTE_CODE_BYTES, len);
      msg->route.route_code |= (data[offset++] & 0xff) << 8;
      msg->route.route_code |= data[offset++] & 0xff;
    } else {
      PC__MSG_CHECK_LEN(offset + PC_MSG_ROUTE_LEN_BYTES, len);
      size_t route_len = data[offset++];

      if(route_len) {
        route_str = (char *)malloc(route_len + 1);
        if(route_str == NULL) {
          fprintf(stderr, "Fail to malloc for message route string.\n");
          goto error;
        }

        PC__MSG_CHECK_LEN(offset + route_len, len);
        memset(route_str, 0, route_len + 1);
        memcpy(route_str, data + offset, route_len);
        msg->route.route_str = route_str;
      }

      offset += route_len;
    }
  }

  // body
  size_t body_len = len - offset;
  if(body_len) {
    body = (char *)malloc(body_len);
    memcpy(body, data + offset, body_len);
  }
  msg->body.base = body;
  msg->body.len = body_len;

  return msg;

error:
  if(msg) free(msg);
  if(route_str) free((void *)route_str);
  if(body) free(body);
  return NULL;
}

static inline size_t pc__msg_encode_flag(pc_msg_type type, int compressRoute,
                                  char *base, size_t offset) {
  base[offset++] = (type << 1) | (compressRoute ? 1 : 0);
  return offset;
}

static inline size_t pc__msg_encode_id(uint32_t id, char *base, size_t offset) {
  do{
      uint32_t tmp = id % 128;
      uint32_t next = id / 128;

      if(next != 0){
        tmp = tmp + 128;
      }
      base[offset++] = tmp;
      id = next;
    } while(id != 0);

  return offset;
}

static inline size_t pc__msg_encode_route(const char *route, uint16_t route_len,
                                   char *base, size_t offset) {
  base[offset++] = route_len & 0xff;

  memcpy(base + offset, route, route_len);

  return offset + route_len;
}

static uint8_t pc__msg_id_length(uint32_t id) {
  uint8_t len = 0;
  do {
    len += 1;
    id >>= 7;
  } while(id > 0);
  return len;
}

void pc_msg_destroy(pc_msg_t *msg) {
  if(msg == NULL) return;
  if(msg->route) free((void *)msg->route);
  if(msg->msg) {
    json_decref(msg->msg);
    msg->msg = NULL;
  }
  free(msg);
}

void pc__raw_msg_destroy(pc__msg_raw_t *msg) {
  if(!msg->compressRoute && msg->route.route_str) {
    free((void *)msg->route.route_str);
  }
  if(msg->body.len > 0) {
    free(msg->body.base);
  }
  free(msg);
}