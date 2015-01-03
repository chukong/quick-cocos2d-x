#include <string.h>
#include "jansson.h"
#include "pomelo-protocol/message.h"

pc_buf_t pc__json_encode(const json_t *msg) {
  pc_buf_t buf;
  char *res = json_dumps(msg, JSON_COMPACT);
  if(res == NULL) {
    fprintf(stderr, "Fail to json encode for message.\n");
    buf.base = NULL;
    buf.len = -1;
  } else {
    buf.base = res;
    buf.len = strlen(res);
  }
  return buf;
}

json_t *pc__json_decode(const char *data, size_t offset, size_t len) {
  json_error_t error;

  json_t *res = json_loadb(data + offset, len - offset, 0, &error);

  if(res == NULL) {
    fprintf(stderr, "Fail to decode json: %s\n", error.text);
    char str[128];
    memset(str, 0, 128);
    memcpy(str, data + offset, len);
    return NULL;
  }

  return res;
}
