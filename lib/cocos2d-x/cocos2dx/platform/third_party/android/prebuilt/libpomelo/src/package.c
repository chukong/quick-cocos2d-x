#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pomelo-private/internal.h"
#include "pomelo-private/common.h"
#include "pomelo-protocol/package.h"

static size_t pc__pkg_head(pc_pkg_parser_t *parser,
                           const char *data, size_t offset, size_t nread);
static size_t pc__pkg_body(pc_pkg_parser_t *parser,
                           const char *data, size_t offset, size_t nread);

pc_pkg_parser_t *pc_pkg_parser_new(pc_pkg_cb cb, void *attach) {
  pc_pkg_parser_t *parser = (pc_pkg_parser_t *)malloc(sizeof(pc_pkg_parser_t));
  if(parser == NULL) {
    fprintf(stderr, "Fail to malloc for pc_pkg_parser_t.\n");
    return NULL;
  }

  memset(parser, 0, sizeof(pc_pkg_parser_t));

  if(pc_pkg_parser_init(parser, cb, attach)) {
    free(parser);
    return NULL;
  }

  return parser;
}

int pc_pkg_parser_init(pc_pkg_parser_t *parser, pc_pkg_cb cb, void *attach) {
  parser->head_size = PC_PKG_HEAD_BYTES;
  parser->cb = cb;
  parser->attach = attach;
  parser->head_offset = 0;
  parser->pkg_offset = 0;
  parser->pkg_size = 0;
  parser->state = PC_PKG_HEAD;

  return 0;
}

void pc_pkg_parser_destroy(pc_pkg_parser_t *parser) {
  pc_pkg_parser_close(parser);
  free(parser);
}

void pc_pkg_parser_close(pc_pkg_parser_t *parser) {
  if(PC_PKG_CLOSED == parser->state) {
    return;
  }

  parser->state = PC_PKG_CLOSED;

  if(parser->pkg_buf) {
    free(parser->pkg_buf);
  }
}

void pc_pkg_parser_reset(pc_pkg_parser_t *parser) {
  if(PC_PKG_CLOSED == parser->state) {
    return;
  }

  parser->head_offset = 0;
  if(parser->pkg_buf) {
    free(parser->pkg_buf);
  }
  parser->pkg_buf = NULL;
  parser->pkg_offset = 0;
  parser->pkg_size = 0;
  parser->state = PC_PKG_HEAD;
};

int pc_pkg_parser_feed(pc_pkg_parser_t *parser, const char *data, size_t nread) {
  size_t offset = 0;

  while(offset < nread) {
    if(parser->state == PC_PKG_HEAD) {
      offset = pc__pkg_head(parser, data, offset, nread);
      if(offset == -1) {
        return -1;
      }
    }

    if(parser->state == PC_PKG_BODY) {
      offset = pc__pkg_body(parser, data, offset, nread);
      if(offset == -1) {
        return -1;
      }
    }

    if(parser->state == PC_PKG_CLOSED) {
      return 0;
    }

    if(parser->state != PC_PKG_HEAD && parser->state != PC_PKG_BODY &&
       parser->state != PC_PKG_CLOSED) {
      fprintf(stderr, "Invalid package parser state: %d\n", parser->state);
      return -1;
    }
  }

  return 0;
}

pc_buf_t pc_pkg_encode(pc_pkg_type type, const char *data, size_t len) {
  pc_buf_t buf;
  if(len >= PC_PKG_MAX_BODY_BYTES) {
    fprintf(stderr, "Data is to large for Pomelo package. Body limit: %d.\n",
            PC_PKG_MAX_BODY_BYTES);
    buf.len = -1;
    return buf;
  }

  size_t size = PC_PKG_HEAD_BYTES + len;
  buf.base = (char *)malloc(size);
  if(buf.base == NULL) {
    fprintf(stderr, "Fail to malloc for Pomelo package, size: %lu.\n", size);
    buf.len = -1;
    return buf;
  }

  memset(buf.base, 0, size);

  buf.base[0] = type & PC_PKG_TYPE_MASK;
  char *base = buf.base + (PC_PKG_HEAD_BYTES - 1);

  if(len) {
    size_t body_size = len;
    int i;
    for(i=0; i<PC_PKG_BODY_LEN_BYTES; i++, base--) {
      *base = body_size % 0x100;
      body_size >>= 8;
    }

    memcpy(buf.base + PC_PKG_HEAD_BYTES, data, len);
  } else {
    // body is empty
  }

  buf.len = size;

  return buf;
}

/**
 * Read package head from data buffer.
 *
 * @param  parser package parser instance
 * @param  data   data buffer
 * @param  offset offset of data buffer
 * @return        new offset of data buffer or -1 for malloc fail
 */
static size_t pc__pkg_head(pc_pkg_parser_t *parser,
                           const char *data, size_t offset, size_t nread) {
  size_t need_len = parser->head_size - parser->head_offset;
  size_t data_len = nread - offset;
  size_t len = MIN(need_len, data_len);

  memcpy(parser->head_buf + parser->head_offset, data + offset, len);
  parser->head_offset += len;

  if(parser->head_offset == parser->head_size) {
    size_t pkg_len = 0;
    int i;
    for(i=1; i<PC_PKG_HEAD_BYTES; i++) {
      if(i > 1) {
        pkg_len <<= 8;
      }
      pkg_len += parser->head_buf[i] & 0xff;
    }

    if(pkg_len > 0) {
      parser->pkg_buf = (char *)malloc(pkg_len);
      if(parser->pkg_buf == NULL) {
        fprintf(stderr, "Fail to malloc buffer for package size: %lu\n", pkg_len);
        return -1;
      }

      memset(parser->pkg_buf, 0, pkg_len);
    }

    parser->pkg_offset = 0;
    parser->pkg_size = pkg_len;
    parser->state = PC_PKG_BODY;
  }

  return offset + len;
}

/**
 * Read package body from data buffer.
 *
 * @param  parser package parser instance
 * @param  data   data buffer
 * @param  offset offset of data buffer
 * @return        new offset of data buffer or -1 for malloc fail
 */
static size_t pc__pkg_body(pc_pkg_parser_t *parser,
                           const char *data, size_t offset, size_t nread) {
  size_t need_len = parser->pkg_size - parser->pkg_offset;
  size_t data_len = nread - offset;
  size_t len = MIN(need_len, data_len);

  if(len > 0) {
    memcpy(parser->pkg_buf + parser->pkg_offset, data + offset, len);
    parser->pkg_offset += len;
  }

  if(parser->pkg_offset == parser->pkg_size) {
    // if all the package finished
    parser->cb((pc_pkg_type)pc__pkg_type(parser->head_buf),
               parser->pkg_buf, parser->pkg_size, parser->attach);
    pc_pkg_parser_reset(parser);
  }

  return offset + len;
}