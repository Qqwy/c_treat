#include "hash_map.ih"

size_t _HashMap_index (HashMap const *hash_map, void *const key) {
  size_t index = ((size_t) key) % hash_map->capacity; // TODO Hashing function!
  while (hash_map->keys[index] != NULL && hash_map->keys[index] != key) {
    /* printf("HTC: %lu, Not storing %s at key %lu because already filled by %s => %s\n", hash_map->capacity, key, index, hash_map->keys[index], hash_map->values[index]); */
    index = (index + 1) % hash_map->capacity;
  }
  return index;
}
