#ifndef POMELO_PACKAGE_H
#define POMELO_PACKAGE_H

#include "uv.h"
#include "jansson.h"
#include "pomelo.h"

/**
 * Pomelo package format:
 * +------+-------------+------------------+
 * | type | body length |       body       |
 * +------+-------------+------------------+
 *
 * Head: 4bytes
 *   0: package type, see as pc_pkg_type
 *   1 - 3: big-endian body length
 * Body: body length bytes
 */

#define PC_PKG_TYPE_MASK 0xff
#define PC_PKG_TYPE_BYTES 1
#define PC_PKG_BODY_LEN_BYTES 3
#define PC_PKG_HEAD_BYTES (PC_PKG_TYPE_BYTES + PC_PKG_BODY_LEN_BYTES)
#define PC_PKG_MAX_BODY_BYTES (1 << 24)

#define pc__pkg_type(head) (head[0] & 0xff)

#define PC_HANDSHAKE_OK 200

#define PC_HEARTBEAT_TIMEOUT_FACTOR 2

 /**
 * New Pomelo package arrived callback.
 *
 * @param  type   package type, refer: pc_pkg_type.
 * @param  data   package body in bytes
 * @param  len    package body length in bytes
 * @param  attach attach pointer passed to package parser before
 */
typedef void (*pc_pkg_cb)(pc_pkg_type type, const char *data,
              size_t len, void *attach);

 /**
 * Structure for Pomelo package parser which provided the service to collect
 * the raw data from lower layer (such as tcp) and parse them into Pomleo
 * package.
 */
struct pc_pkg_parser_s {
  /*! Buffer for package header bytes. */
  char head_buf[PC_PKG_HEAD_BYTES];
  /*! Buffer for package body bytes. */
  char *pkg_buf;

  /*! Offset of header buffer. */
  size_t head_offset;
  /*! Size of header buffer. */
  size_t head_size;

  /*! Offset of body buffer. */
  size_t pkg_offset;
  /*! Size of body buffer. */
  size_t pkg_size;

  /*! New Package arrived callback. */
  pc_pkg_cb cb;
  /*! Attach pointer that would be pass to pc_pkg_cb. */
  void *attach;

  /*! State of the package parser. */
  pc_pkg_parser_state state;
};

/**
 * Create a Pomelo package parser.
 *
 * @param  cb     new package arrived callback.
 * @param  attach attach pointer that would be pass to package arrived callback.
 * @return        new package parser instance.
 */
pc_pkg_parser_t *pc_pkg_parser_new(pc_pkg_cb cb, void *attach);

/**
 * Destroy a Pomelo package parser instance, release the inner resources and the
 * package parser. This function is used as couple with pc_pkg_parser_new.
 *
 * @param parser pointer to package parser.
 */
void pc_pkg_parser_destroy(pc_pkg_parser_t *parser);

/**
 * Initiate a block allocated memory for package parser. Normally, using
 * pc_pkg_parser_new is enough.
 *
 * @param  pro    allocated memory for package parser instance.
 * @param  cb     new package arrived callback.
 * @param  attach attach pointer that would be pass to package arrived callback.
 * @return        0 for ok and -1 for fails.
 */
int pc_pkg_parser_init(pc_pkg_parser_t *pro, pc_pkg_cb cb, void *attach);

/**
 * Close a package parser and release the inner resources. But NOT release the
 * parser itself. This function is used as couple with pc_pkg_parser_init.
 *
 * @param parser pointer to package parser.
 */
void pc_pkg_parser_close(pc_pkg_parser_t *parser);

/**
 * Reset the package parser state to the initiated state.
 *
 * @param pro pointer to package parser.
 */
void pc_pkg_parser_reset(pc_pkg_parser_t *pro);

/**
 * Feed data to the package parser which would fire the state machine of the
 * parser to parse the header or body of the package.
 *
 * @param  pro   pointer of package parser.
 * @param  data  new data to feed.
 * @param  nread length of data.
 * @return       0 for ok and -1 for error.
 */
int pc_pkg_parser_feed(pc_pkg_parser_t *pro, const char *data, size_t nread);

/**
 * Encode data to Pomelo package.
 *
 * @param  type Pomelo package type, refer: pc_pkg_type.
 * @param  data data to encode.
 * @param  len  length of data.
 * @return      buffer for encode result. buf.len = -1 for error.
 */
pc_buf_t pc_pkg_encode(pc_pkg_type type, const char *data, size_t len);

#endif /* POMELO_PACKAGE_H */