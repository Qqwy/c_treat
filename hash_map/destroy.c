#include "hash_map.ih"

void HashMap_destroy(HashMap *hash_map) {
  free(hash_map->values);
  free(hash_map->keys);
  free(hash_map);
}
