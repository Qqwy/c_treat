#include "hash_map.ih"

void HashMap_insert(HashMap **hash_map_ref, void *const key, void *const value) {
  HashMap *hash_map = *hash_map_ref;
  size_t const index = _HashMap_index(hash_map, key);
  /* printf("HTC: %lu, Inserting %s at index %lu\n", hash_map->capacity, key, index); */
  hash_map->keys[index] = key;
  if(hash_map->values[index] == NULL) // Table increases in size only if previous key was not replaced.
    ++(hash_map->size);
  hash_map->values[index] = value;

  if(hash_map->size * 4 >= hash_map->capacity * 3) { // 3/4 maximum load factor.
    _HashMap_resize(hash_map_ref);
  }
}
