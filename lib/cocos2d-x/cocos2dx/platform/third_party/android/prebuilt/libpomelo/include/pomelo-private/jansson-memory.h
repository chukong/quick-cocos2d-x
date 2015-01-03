#ifndef PC_MEMORY_H
#define PC_MEMORY_H

#include "pomelo.h"

/* Wrappers for custom memory functions */
void* pc_jsonp_malloc(size_t size);
void pc_jsonp_free(void *ptr);

#endif