/* pb_encode.c -- encode a protobuf using minimal resources
 *
 * 2013 fantasyni <fantasyni@163.com>
 */

//#define PB_INTERNALS
//#define PB_DEBUG
//#define __BIG_ENDIAN__
#include "pomelo-protobuf/pb.h"
#include "pomelo-protobuf/pb-util.h"
#include <string.h>

/* The warn_unused_result attribute appeared first in gcc-3.4.0 */
#if !defined(__GNUC__) || ( __GNUC__ < 3) || (__GNUC__ == 3 && __GNUC_MINOR__ < 4)
#define checkreturn
#else
/* Verify that we remember to check all return values for proper error propagation */
#define checkreturn __attribute__((warn_unused_result))
#endif

typedef struct _pb_ostream_t pb_ostream_t;

/* Lightweight output stream.
 * You can provide callback for writing or use pb_ostream_from_buffer.
 *
 * Alternatively, callback can be NULL in which case the stream will just
 * count the number of bytes that would have been written. In this case
 * max_size is not checked.
 *
 * Rules for callback:
 * 1) Return 0 on IO errors. This will cause encoding to abort.
 *
 * 2) You can use state to store your own data (e.g. buffer pointer).
 *
 * 3) pb_write will update bytes_written after your callback runs.
 *
 * 4) Substreams will modify max_size and bytes_written. Don't use them to
 * calculate any pointers.
 */
struct _pb_ostream_t {
    int (*callback)(pb_ostream_t *stream, const uint8_t *buf, size_t count);
    void *state; /* Free field for use by callback implementation */
    size_t max_size; /* Limit number of output bytes written (or use SIZE_MAX). */
    size_t bytes_written;
};

static int pb_encode(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos, json_t *msg);

static pb_ostream_t pb_ostream_from_buffer(uint8_t *buf, size_t bufsize);
static int pb_write(pb_ostream_t *stream, const uint8_t *buf, size_t count);


/* --- Helper functions ---
 * You may want to use these from your caller or callbacks.
 */

static int pb_encode_proto(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos, const json_t *proto, json_t *value);

static int pb_encode_array(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos, const json_t *proto, json_t *array);
/* Encode field header based on LTYPE and field number defined in the field structure.
 * Call this from the callback before writing out field contents. */
static int pb_encode_tag_for_field(pb_ostream_t *stream, const json_t *field);

/* Encode field header by manually specifing wire type. You need to use this if
 * you want to write out packed arrays from a callback field. */
static int pb_encode_tag(pb_ostream_t *stream, int wiretype, uint32_t field_number);

/* Encode an integer in the varint format.
 * This works for int, enum, int32, int64, uint32 and uint64 field types. */
static int pb_encode_varint(pb_ostream_t *stream, uint64_t value);

/* Encode an integer in the zig-zagged svarint format.
 * This works for sint32 and sint64. */
static int pb_encode_svarint(pb_ostream_t *stream, int64_t value);

/* Encode a string or bytes type field. For strings, pass strlen(s) as size. */
static int pb_encode_string(pb_ostream_t *stream, const uint8_t *buffer, size_t size);

/* Encode a fixed32, sfixed32 or float value.
 * You need to pass a pointer to a 4-byte wide C variable. */
static int pb_encode_fixed32(pb_ostream_t *stream, const void *value);

/* Encode a fixed64, sfixed64 or double value.
 * You need to pass a pointer to a 8-byte wide C variable. */
static int pb_encode_fixed64(pb_ostream_t *stream, const void *value);

/* Eecode submessage in __messages protos */
static int pb_encode_submessage(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos, json_t *value);
/* pb_ostream_t implementation */

int pc_pb_encode(uint8_t *buf, size_t len, size_t *written, const json_t *gprotos, const json_t *protos, json_t *msg) {
    pb_ostream_t stream = pb_ostream_from_buffer(buf, len);
    if (!pb_encode(&stream, gprotos, protos, msg)) {
        fprintf(stderr, "pb_encode error\n");
        return 0;
    }
    *written = stream.bytes_written;
    return 1;
}

static int checkreturn buf_write(pb_ostream_t *stream, const uint8_t *buf,
                                 size_t count) {
    uint8_t *dest = (uint8_t *) stream->state;
    memcpy(dest, buf, count);
    stream->state = dest + count;
    return 1;
}

static pb_ostream_t pb_ostream_from_buffer(uint8_t *buf, size_t bufsize) {
    pb_ostream_t stream;
    stream.callback = &buf_write;
    stream.state = buf;
    stream.max_size = bufsize;
    stream.bytes_written = 0;
    return stream;
}

static int checkreturn pb_write(pb_ostream_t *stream, const uint8_t *buf,
                                size_t count) {
    if (stream->callback != NULL ) {
        if (stream->bytes_written + count > stream->max_size)
            return 0;

        if (!stream->callback(stream, buf, count))
            return 0;
    }

    stream->bytes_written += count;
    return 1;
}

/* Main encoding stuff */

static int checkreturn pb_encode_array(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos,
                                       const json_t *proto, json_t *array) {
    json_t *type = json_object_get(proto, "type");
    const char *type_text = json_string_value(type);
    size_t len = json_array_size(array);
    size_t i;
    // simple msg
    if (pb__get_type(type_text) && pb__get_type(type_text) != PB_string) {
        if (!pb_encode_tag_for_field(stream, proto)) {
            return 0;
        }

        if (!pb_encode_varint(stream, len)) {
            return 0;
        }
        for (i = 0; i < len; i++) {
            if (!pb_encode_proto(stream, gprotos, protos, proto,
                                 json_array_get(array, i))) {
                return 0;
            }
        }
    } else {
        for (i = 0; i < len; i++) {
            if (!pb_encode_tag_for_field(stream, proto)) {
                return 0;
            }
            if (!pb_encode_proto(stream, gprotos, protos, proto,
                                 json_array_get(array, i))) {
                return 0;
            }
        }
    }
    return 1;
}

static int checkreturn pb_encode(pb_ostream_t *stream, const json_t *gprotos,
                                 const json_t *protos, json_t *msg) {
    json_t *root, *value, *option, *proto;
    root = msg;

    const char *option_text;
    const char *key;
    void *iter = json_object_iter(root);
    while (iter) {
        key = json_object_iter_key(iter);
        value = json_object_iter_value(iter);

        proto = json_object_get(protos, key);
        if (proto) {
            option = json_object_get(proto, "option");
            option_text = json_string_value(option);
            if (strcmp(option_text, "required") == 0
                    || strcmp(option_text, "optional") == 0) {
                if (!pb_encode_tag_for_field(stream, proto)) {
                    return 0;
                }

                if (!pb_encode_proto(stream, gprotos, protos, proto, value)) {
                    return 0;
                }
            } else if (strcmp(option_text, "repeated") == 0) {
                if (json_is_array(value)) {
                    if (!pb_encode_array(stream, gprotos, protos, proto, value)) {
                        return 0;
                    }
                }
            }
        } else {
            return 0;
        }
        iter = json_object_iter_next(root, iter);
    }
    return 1;
}

static int checkreturn pb_encode_proto(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos,
                                       const json_t *proto, json_t *value) {
    json_t *_messages;
    json_t *_type = json_object_get(proto, "type");
    json_t *sub_msg;
    const char *type = json_string_value(_type);
    const char *str;
    json_int_t int_val;
    float float_val;
    double double_val;
    int length;

    _messages = json_object_get(protos, "__messages");
    switch (pb__get_type(type)) {
    case PB_uInt32:
        int_val = json_number_value(value);
        if (!pb_encode_varint(stream, int_val)) {
            return 0;
        }
        break;
    case PB_int32:
    case PB_sInt32:
        int_val = json_number_value(value);
        if (!pb_encode_svarint(stream, int_val)) {
            return 0;
        }
        break;
    case PB_float:
        float_val = json_number_value(value);
        if (!pb_encode_fixed32(stream, &float_val)) {
            return 0;
        }
        break;
    case PB_double:
        double_val = json_number_value(value);
        if (!pb_encode_fixed64(stream, &double_val)) {
            return 0;
        }
        break;
    case PB_string:
        str = json_string_value(value);
        length = strlen(str);
        if (!pb_encode_string(stream, (const uint8_t *)str, length)) {
            return 0;
        }
        break;
    default:
        if (_messages) {
            sub_msg = json_object_get(_messages, type);
            if (!sub_msg) {
                // check root msg in gprotos
                const char *head = "message ";
                size_t len = strlen(head) + strlen(type) + 1;
                char *head_text = (char *)malloc(len);
                memset(head_text, 0, len);
                strcpy(head_text, head);
                strcat(head_text, type);
                sub_msg = json_object_get(gprotos, head_text);
                free(head_text);
            }
            if (sub_msg) {
                if (!pb_encode_submessage(stream, gprotos, sub_msg, value)) {
                    return 0;
                }
            } else {
                return 0;
            }
        }

    }
    return 1;
}

/* Helper functions */

/* Encode an integer in the varint format.
 * This works for bool, enum, int32, int64, uint32 and uint64 field types. */
static int checkreturn pb_encode_varint(pb_ostream_t *stream, uint64_t value) {
    uint8_t buffer[10];
    size_t i = 0;

    if (value == 0)
        return pb_write(stream, (uint8_t *) &value, 1);

    while (value) {
        buffer[i] = (uint8_t)((value & 0x7F) | 0x80);
        value >>= 7;
        i++;
    }
    buffer[i - 1] &= 0x7F; /* Unset top bit on last byte */

    return pb_write(stream, buffer, i);
}

/* Encode an integer in the zig-zagged svarint format.
 * This works for sint32 and sint64. */
static int checkreturn pb_encode_svarint(pb_ostream_t *stream, int64_t value) {
    uint64_t zigzagged;
    if (value < 0)
        zigzagged = (uint64_t)(~(value << 1));
    else
        zigzagged = (uint64_t)(value << 1);

    return pb_encode_varint(stream, zigzagged);
}

/* Encode a fixed32, sfixed32 or float value.
 * You need to pass a pointer to a 4-byte wide C variable. */
static int checkreturn pb_encode_fixed32(pb_ostream_t *stream, const void *value) {
#ifdef __BIG_ENDIAN__
    const uint8_t *bytes = value;
    uint8_t lebytes[4];
    lebytes[0] = bytes[3];
    lebytes[1] = bytes[2];
    lebytes[2] = bytes[1];
    lebytes[3] = bytes[0];
    return pb_write(stream, lebytes, 4);
#else
    return pb_write(stream, (const uint8_t *) value, 4);
#endif
}

/* Encode a fixed64, sfixed64 or double value.
 * You need to pass a pointer to a 8-byte wide C variable. */
static int checkreturn pb_encode_fixed64(pb_ostream_t *stream, const void *value) {
#ifdef __BIG_ENDIAN__
    const uint8_t *bytes = value;
    uint8_t lebytes[8];
    lebytes[0] = bytes[7];
    lebytes[1] = bytes[6];
    lebytes[2] = bytes[5];
    lebytes[3] = bytes[4];
    lebytes[4] = bytes[3];
    lebytes[5] = bytes[2];
    lebytes[6] = bytes[1];
    lebytes[7] = bytes[0];
    return pb_write(stream, lebytes, 8);
#else
    return pb_write(stream, (const uint8_t *) value, 8);
#endif
}

/* Encode field header by manually specifing wire type. You need to use this if
 * you want to write out packed arrays from a callback field. */
static int checkreturn pb_encode_tag(pb_ostream_t *stream, int wiretype,
                                     uint32_t field_number) {
    uint64_t tag = wiretype | (field_number << 3);
    return pb_encode_varint(stream, tag);
}

/* Encode field header based on LTYPE and field number defined in the field structure.
 * Call this from the callback before writing out field contents. */
static int checkreturn pb_encode_tag_for_field(pb_ostream_t *stream, const json_t *field) { // type,tag
    int wiretype;
    json_t *type = json_object_get(field, "type");
    json_t *tag = json_object_get(field, "tag");

    wiretype = pb__get_constant_type(json_string_value(type));

    return pb_encode_tag(stream, wiretype, json_number_value(tag));
}

/* Encode a string or bytes type field. For strings, pass strlen(s) as size. */
static int checkreturn pb_encode_string(pb_ostream_t *stream, const uint8_t *buffer,
                                        size_t size) {
    if (!pb_encode_varint(stream, (uint64_t) size))
        return 0;

    return pb_write(stream, buffer, size);
}

/* Eecode submessage in __messages protos */
static int pb_encode_submessage(pb_ostream_t *stream, const json_t *gprotos, const json_t *protos, json_t *value) {
    /* First calculate the message size using a non-writing substream. */
    pb_ostream_t substream = { 0, 0, 0, 0 };
    size_t size;
    int status;

    if (!pb_encode(&substream, gprotos, protos, value)) {
        return 0;
    }

    size = substream.bytes_written;

    if (!pb_encode_varint(stream, (uint64_t) size)) {
        return 0;
    }

    if (stream->callback == NULL )
        return pb_write(stream, NULL, size); /* Just sizing */

    if (stream->bytes_written + size > stream->max_size)
        return 0;

    /* Use a substream to verify that a callback doesn't write more than
     * what it did the first time. */
    substream.callback = stream->callback;
    substream.state = stream->state;
    substream.max_size = size;
    substream.bytes_written = 0;

    status = pb_encode(&substream, gprotos, protos, value);

    stream->bytes_written += substream.bytes_written;
    stream->state = substream.state;

    if (substream.bytes_written != size) {
        return 0;
    }

    return status;
}
