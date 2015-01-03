#include <stdlib.h>
#include "uv.h"

void pc__handle_close_cb(uv_handle_t* handle) {
  free(handle);
}