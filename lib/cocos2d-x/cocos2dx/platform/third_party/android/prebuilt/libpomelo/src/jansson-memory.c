#include <stdlib.h>
#include <string.h>

#include "jansson.h"
#include "pomelo.h"
#include "pomelo-private/jansson-memory.h"

/* memory function pointers */
static json_malloc_t do_malloc = malloc;
static json_free_t do_free = free;

void *pc_jsonp_malloc(size_t size)
{
    if(!size)
        return NULL;

    return (*do_malloc)(size);
}

void pc_jsonp_free(void *ptr)
{
    if(!ptr)
        return;

    (*do_free)(ptr);
}

void pc_json_set_alloc_funcs(json_malloc_t malloc_fn, json_free_t free_fn)
{
	json_set_alloc_funcs(malloc_fn, free_fn);
	do_malloc = malloc_fn;
	do_free = free_fn;
}
