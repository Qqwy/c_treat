#include "alloc.ih"

void *safe_calloc(size_t n_items, size_t item_size) {
  void * ptr = calloc(n_items, item_size);
  if(ptr == NULL) {
    perror("Error during calloc allocation");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
