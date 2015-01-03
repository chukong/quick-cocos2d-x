#ifndef PC_MESSAGE_H
#define PC_MESSAGE_H

#include "jansson.h"
#include "pomelo.h"

/**
 * More information of Pomelo message format, refer to https://github.com/NetEase/pomelo/wiki/Pomelo-%E9%80%9A%E8%AE%AF%E5%8D%8F%E8%AE%AE .
 * And about the compress of dictionary and protobuf in Pomelo, refer to https://github.com/NetEase/pomelo/wiki/Pomelo-%E6%95%B0%E6%8D%AE%E5%8E%8B%E7%BC%A9%E5%8D%8F%E8%AE%AE .
 */

#define PC_MSG_FLAG_BYTES 1

#define PC_MSG_ROUTE_LEN_BYTES 1

#define PC_MSG_ROUTE_CODE_BYTES 2

#define PC_MSG_HAS_ID(TYPE) ((TYPE) == PC_MSG_REQUEST ||                      \
                             (TYPE) == PC_MSG_RESPONSE)

#define PC_MSG_HAS_ROUTE(TYPE) ((TYPE) != PC_MSG_RESPONSE)

#define PC_MSG_VALIDATE(TYPE) ((TYPE) == PC_MSG_REQUEST ||                    \
                               (TYPE) == PC_MSG_NOTIFY ||                     \
                               (TYPE) == PC_MSG_RESPONSE ||                   \
                               (TYPE) == PC_MSG_PUSH)

#define PC__MSG_CHECK_LEN(INDEX, LENGTH) do {                                 \
  if((INDEX) > (LENGTH)) {                                                    \
    goto error;                                                               \
  }                                                                           \
}while(0);

#define PC_PB_EVAL_FACTOR 2

/**
 * Types of message.
 */
typedef enum {
  PC_MSG_REQUEST = 0,
  PC_MSG_NOTIFY,
  PC_MSG_RESPONSE,
  PC_MSG_PUSH
} pc_msg_type;

/**
 * Raw message struture which has parsed message header but not uncompress
 * route string and body.
 */
typedef struct {
  /*! Message id. */
  uint32_t id;
  /*! Message type. */
  pc_msg_type type;
  /*! Compress flag of message route string. 0: not compress; 1: compres. */
  uint8_t compressRoute;
  /*! Rout information of message. Route string or code which decided by compressRoute. */
  union {
    uint16_t route_code;
    const char *route_str;
  } route;
  /*! Message body in bytes. */
  pc_buf_t body;
} pc__msg_raw_t;

/**
 * Encode message with route string.
 *
 * @param  id    message id. positive for request and 0 for notify.
 * @param  type  message type, PC_MSG_REQUEST or PC_MSG_NOTIFY.
 * @param  route route string which would not compressed by dictionary.
 * @param  msg   message content in bytes which has encoded byte upper layer, such as json or protobuf.
 * @return       encode result in bytes. buf.len -1 for error.
 */
pc_buf_t pc_msg_encode_route(uint32_t id, pc_msg_type type,
                             const char *route, pc_buf_t msg);

/**
 * Encode message with route code.
 *
 * @param  id         message id. positive for request and 0 for notify.
 * @param  type       message type, PC_MSG_REQUEST or PC_MSG_NOTIFY.
 * @param  route_code route code, the route string compressed by dinctionary.
 * @param  msg        message content in bytes which has encoded byte upper layer, such as json or protobuf.
 * @return            encode result in bytes. buf.len -1 for error.
 */
pc_buf_t pc_msg_encode_code(uint32_t id, pc_msg_type type,
                            int route_code, pc_buf_t msg);

/**
 * Decode message header but not uncompress route and body.
 *
 * @param  data message data in bytes.
 * @param  len  length of message data.
 * @return      raw message structure or NULL for error.
 */
pc__msg_raw_t *pc_msg_decode(const char *data, size_t len);

/**
 * Destroy raw message structure and release inner resources.
 *
 * @param msg pointer to raw message structure.
 */
void pc__raw_msg_destroy(pc__msg_raw_t *msg);

/**
 * Destroy message structure.
 *
 * @param msg pointer to message structure.
 */
void pc_msg_destroy(pc_msg_t *msg);

/**
 * Encode message body with json.
 *
 * @param  msg message body structure.
 * @return     encode result in bytes, buf.len = -1 for error. buf.base should be released by free() outside.
 */
pc_buf_t pc__json_encode(const json_t *msg);

/**
 * Decode message body with json.
 *
 * @param  data   data of message body in bytes.
 * @param  offset offset of data.
 * @param  len    length of data.
 * @return        decode result or NULL for error. Result should be released by json_decref() outside.
 */
json_t *pc__json_decode(const char *data, size_t offset, size_t len);

/**
 * Do protobuf encode for message. The pc_buf_t returned contains the encode
 * result in buf.base and the size of the data in buf.len which should be
 * positive and should be -1 stand for error. And if success, the buf.base MUST
 * be released by free().
 *
 * @param  msg    json message to be encoded
 * @param  pb_def protobuf definition for the message
 * @return        encode result and buf.len = -1 for error. buf.base should be released by free() outside.
 */
pc_buf_t pc__pb_encode(const json_t *msg, const json_t *gprotos, const json_t *pb_def);

/**
 * Do protobuf decode for the binary data. The return json_t object could be
 * used as normal json_t object and call json_decref() to released.
 *
 * @param data    binary data to decode
 * @param offset  offset of the data
 * @param len     lenght of the data
 * @param pb_def  protobuf definition for the data
 * @return        decode result or NULL for error. Result should be released by json_decref() outside.
 */
json_t *pc__pb_decode(const char *data, size_t offset, size_t len,
                      const json_t *gprotos, const json_t *pb_def);

#endif /* PC_MESSAGE_H */