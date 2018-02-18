#include "alloc.ih"

void *safe_malloc(size_t size) {
  void * ptr = malloc(size);
  if(ptr == NULL) {
    perror("Error during malloc allocation");
    exit(EXIT_FAILURE);
  }
  return ptr;
}
