#include "hash_map.ih"

size_t _HashMap_index (HashMap const *hash_map, void *const key) {
  // Note: We're not using a hashing function here,
  // but are trusting the uniformness of the system's memory location remapping system.
  size_t index = ((size_t) key) % hash_map->capacity;
  while (hash_map->keys[index] != NULL && hash_map->keys[index] != key) {
    index = (index + 1) % hash_map->capacity;
  }
  return index;
}
