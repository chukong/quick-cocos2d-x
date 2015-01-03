#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "pomelo-private/map.h"

static size_t pc__hash(const char *str) {
  size_t hash = 0;
  size_t c;

  while((c = (size_t)*str)) {
    hash += c;
    str++;
  }

  return hash;
}

pc_map_t *pc_map_new(size_t capacity, pc_map_value_release release_value) {
  pc_map_t *map = (pc_map_t *)malloc(sizeof(pc_map_t));
  if(map == NULL) {
    return NULL;
  }

  memset(map, 0, sizeof(pc_map_t));

  if(pc_map_init(map, capacity, release_value)) {
    free(map);
    return NULL;
  }

  return map;
}

void pc_map_destroy(pc_map_t *map) {
  pc_map_close(map);
  free(map);
}

int pc_map_init(pc_map_t *map, size_t capacity,
                pc_map_value_release release_value) {
  if(capacity < PC__MAP_DEFAULT_CAPACITY) {
    capacity = PC__MAP_DEFAULT_CAPACITY;
  }

  map->capacity = capacity;

  map->buckets = (ngx_queue_t *)malloc(sizeof(ngx_queue_t) * capacity);

  if(map->buckets == NULL) {
    fprintf(stderr, "Fail to malloc for pc_map_t.\n");
    return -1;
  }

  int i;
  for(i=0; i<capacity; i++) {
    ngx_queue_init(&map->buckets[i]);
  }

  map->release_value = release_value;

  return 0;
}

void pc_map_close(pc_map_t *map) {
  pc_map_clear(map);
  free(map->buckets);
  map->buckets = NULL;
}

int pc_map_set(pc_map_t *map, const char *key, void *value) {
  size_t key_len = strlen(key) + 1;
  pc__pair_t *pair = NULL;
  char *cpy_key = NULL;

  pair = (pc__pair_t *)malloc(sizeof(pc__pair_t));
  if(pair == NULL) {
    goto error;
  }
  memset(pair, 0, sizeof(pc__pair_t));
  ngx_queue_init(&pair->queue);

  cpy_key = (char *)malloc(key_len);
  if(cpy_key == NULL) {
    goto error;
  }
  memcpy(cpy_key, key, key_len);

  pair->key = cpy_key;
  pair->value = value;

  size_t hash = pc__hash(key);

  ngx_queue_t *head = &map->buckets[hash % map->capacity];
  ngx_queue_t *q = NULL;
  pc__pair_t *old_pair = NULL;
  ngx_queue_foreach(q, head) {
    old_pair = ngx_queue_data(q, pc__pair_t, queue);
    if(!strcmp(old_pair->key, key)) {
      ngx_queue_remove(q);
      ngx_queue_init(q);
    } else {
      old_pair = NULL;
    }
  }

  ngx_queue_insert_tail(head, &pair->queue);

  if(old_pair) {
    map->release_value(map, old_pair->key, old_pair->value);
    free((void *)old_pair->key);
    free(old_pair);
  }

  return 0;
error:
  if(pair) free(pair);
  if(cpy_key) free(cpy_key);
  return -1;
}

void *pc_map_get(pc_map_t *map, const char *key) {
  size_t hash = pc__hash(key);
  ngx_queue_t *head = &map->buckets[hash % map->capacity];

  ngx_queue_t *q;
  pc__pair_t *pair;
  ngx_queue_foreach(q, head) {
    pair = ngx_queue_data(q, pc__pair_t, queue);
    if(!strcmp(key, pair->key)) {
      return pair->value;
    }
  }

  return NULL;
}

void *pc_map_del(pc_map_t *map, const char *key) {
  size_t hash = pc__hash(key);
  ngx_queue_t *head = &map->buckets[hash % map->capacity];

  ngx_queue_t *q;
  pc__pair_t *pair;
  void *value;
  ngx_queue_foreach(q, head) {
    pair = ngx_queue_data(q, pc__pair_t, queue);
    if(!strcmp(key, pair->key)) {
      ngx_queue_remove(q);
      ngx_queue_init(q);
      value = pair->value;
      free((void *)pair->key);
      free(pair);
      return value;
    }
  }
  return NULL;
}

void pc_map_clear(pc_map_t *map) {
  if(map->buckets == NULL) return;

  int i;
  for(i=0; i<map->capacity; i++) {
    ngx_queue_t *head = &map->buckets[i];

    ngx_queue_t *q;
    pc__pair_t *pair;
    while(!ngx_queue_empty(head)) {
      q = ngx_queue_next(head);
      pair = ngx_queue_data(q, pc__pair_t, queue);
      ngx_queue_remove(q);
      ngx_queue_init(q);
      map->release_value(map, pair->key, pair->value);
      free((void *)pair->key);
      free(pair);
    }
  }
}
