#include "alloc.ih"

void *safe_realloc(void *ptr, size_t size) {
  void * new_ptr = realloc(ptr, size);
  if(size != 0 && ptr == NULL) {
    perror("Error during realloc allocation");
    exit(EXIT_FAILURE);
  }
  return new_ptr;
}
