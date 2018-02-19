#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <sys/types.h>

typedef struct {
  size_t size;
  size_t capacity;
  void **keys;
  void **values;
} HashMap;

HashMap *HashMap_new(size_t capacity);
void HashMap_destroy(HashMap *hash_map);
void HashMap_insert(HashMap **hash_map_ref, void *const key, void *const value);
void *HashMap_lookup(HashMap *hash_map, void *const key);

#endif //HASH_MAP_H
