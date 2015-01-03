#ifdef __cplusplus
extern "C" {
#endif


#ifndef PC_MAP_H
#define PC_MAP_H

#include <stdlib.h>
#include "pomelo-private/ngx-queue.h"

/**
 * Simple hash map implements.
 */

#define PC__MAP_DEFAULT_CAPACITY 64

typedef struct pc_map_s pc_map_t;
typedef struct pc__pair_s pc__pair_t;

/**
 * Map value release callback function which would be fired when the key/value
 * pair is removing from the map.
 *
 * @param  map   pointer to the map instance.
 * @param  key   the key
 * @param  value the value
 */
typedef void (*pc_map_value_release)(pc_map_t *map, const char *key,
                                     void *value);

/**
 * Map structure which used to keep key/value data.
 */
struct pc_map_s {
  /*! Capacity of buckets of map. */
  size_t capacity;
  /*! Array of buckets. */
  ngx_queue_t *buckets;
  /*! Value release callback function which would be invoked before the value released where the map clearing. */
  pc_map_value_release release_value;
};

/**
 * Key/value item for map structure.
 */
struct pc__pair_s {
  const char *key;
  void *value;
  ngx_queue_t queue;
};

/**
 * Create a new map instance.
 *
 * @param  capacity      capacity of map.
 * @param  release_value value release callback for the map.
 * @return               new map instance or NULL for error.
 */
pc_map_t *pc_map_new(size_t capacity, pc_map_value_release release_value);

/**
 * Destroy the map instance. Release all the key/value pair in the map and then
 * release the instance. This function is used as couple with pc_map_new.
 *
 * @param map pointer to the map instance.
 */
void pc_map_destroy(pc_map_t *map);

/**
 * Initiate a block allocated memory for package parser. Normally, using
 * pc_pkg_parser_new is enough.
 *
 * @param  map           allocated memory for map instance.
 * @param  capacity      capacity of map.
 * @param  release_value value release callback for the map.
 * @return               0 for ok and -1 for error.
 */
int pc_map_init(pc_map_t *map, size_t capacity, pc_map_value_release release_value);

/**
 * Close a map instance and release the inner resources. But NOT release the
 * instance itself. This function is used as couple with pc_map_init.
 *
 * @param map pointer of map instance.
 */
void pc_map_close(pc_map_t *map);

/**
 * Add or modify a value in map. If the value with the given key already exists,
 * the value would be replaced and the value release callback would be fired to
 * release the value.
 *
 * @param  map   pointer to map instance.
 * @param  key   key
 * @param  value value
 * @return       0 for ok and -1 for error.
 */
int pc_map_set(pc_map_t *map, const char *key, void *value);

/**
 * Get the value associated with the given key.
 *
 * @param map pointer to the map instance.
 * @param key key
 * @return    the value or NULL for the value not exists.
 */
void *pc_map_get(pc_map_t *map, const char *key);

/**
 * Remove a value from the map.
 *
 * @param map pointer of the map instance.
 * @param key the key
 * @return    the value with the given key or NULL for the value no exists.
 */
void *pc_map_del(pc_map_t *map, const char *key);

/**
 * Clear all the key/value pair in the map.
 *
 * @param map pointer to the map instance.
 */
void pc_map_clear(pc_map_t *map);

#endif  /* PC_MAP_H */

#ifdef __cplusplus
}
#endif