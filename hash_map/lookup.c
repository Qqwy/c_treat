#include "hash_map.ih"

void *HashMap_lookup(HashMap *hash_map, void *const key) {
  size_t const index = _HashMap_index(hash_map, key);
  return hash_map->values[index];
}
