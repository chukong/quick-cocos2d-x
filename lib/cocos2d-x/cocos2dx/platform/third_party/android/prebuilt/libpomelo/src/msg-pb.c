#include <string.h>
#include "jansson.h"
#include "pomelo-protocol/message.h"
#include "pomelo-protobuf/pb.h"
#include "pomelo-private/jansson-memory.h"

pc_buf_t pc__pb_encode(const json_t *msg, const json_t *gprotos, const json_t *pb_def) {
    pc_buf_t buf, json_buf;
    memset(&buf, 0, sizeof(pc_buf_t));
    memset(&json_buf, 0, sizeof(pc_buf_t));

    json_buf = pc__json_encode(msg);

    if (json_buf.len == -1) {
        fprintf(stderr, "Fail to encode json for protobuf evaluate.\n");
        goto error;
    }

    size_t eval_size = json_buf.len * PC_PB_EVAL_FACTOR;

    buf.base = (char *)malloc(eval_size);

    if (buf.base == NULL) {
        fprintf(stderr, "Fail to malloc for protobuf encode.\n");
        buf.len = -1;
        goto error;
    }

    size_t written = 0;
    if (!pc_pb_encode((uint8_t *)buf.base, eval_size, &written,
                      (json_t *)gprotos, (json_t *)pb_def, (json_t *)msg)) {
        fprintf(stderr, "Fail to do protobuf encode.\n");
        goto error;
    }

    buf.len = written;

    pc_jsonp_free(json_buf.base);

    return buf;

error:
    if (json_buf.len == -1 && json_buf.base != NULL) pc_jsonp_free(json_buf.base);
    if (buf.len == -1) {
        free(buf.base);
        buf.base = NULL;
    }
    return buf;
}

json_t *pc__pb_decode(const char *data, size_t offset, size_t len,
                      const json_t *gprotos, const json_t *pb_def) {

    json_t *result = json_object();
    if (result == NULL) {
        fprintf(stderr, "Fail to create json_t for protobuf decode.\n");
        goto error;
    }

    if (!pc_pb_decode((uint8_t *)(data + offset), len,
                      (json_t *)gprotos, (json_t *)pb_def, result)) {
        fprintf(stderr, "Fail to do protobuf decode.\n");
        goto error;
    }

    return result;

error:
    if (result) json_decref(result);

    return NULL;
}
