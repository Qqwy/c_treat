#include "hash_map.ih"

void _HashMap_resize(HashMap **hash_map_ref) {
  HashMap *hash_map = *hash_map_ref;
  HashMap *larger_table = HashMap_new(hash_map->capacity << 1);
  for(size_t iter_index = 0; iter_index < hash_map->capacity; ++iter_index) {
    if(hash_map->keys[iter_index] != NULL){
      HashMap_insert(&larger_table, hash_map->keys[iter_index], hash_map->values[iter_index]);
    }
  }
  *hash_map_ref = larger_table;
  HashMap_destroy(hash_map);
}
