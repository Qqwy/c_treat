#include "hash_map.ih"

HashMap *HashMap_new(size_t capacity) {
  capacity = capacity > 2 ? capacity : 2;
  HashMap *hash_map = calloc(1, sizeof(HashMap));
  hash_map->capacity = capacity;
  hash_map->size = 0;
  hash_map->keys = calloc(capacity, sizeof(void *));
  hash_map->values = calloc(capacity, sizeof(void *));

  return hash_map;
}
