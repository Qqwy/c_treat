#ifndef UTILS_ALLOC_H_
#define UTILS_ALLOC_H_

#include <sys/types.h>

void *safe_malloc(size_t size);
void *safe_calloc(size_t n_items, size_t item_size);
void *safe_realloc(void *ptr, size_t size);

#endif //UTILS_ALLOC_H_
