#include "string.ih"

#include "../../../utils/math.h"

void *String_ctor(void *_self, va_list *args) {
  TString *self = _self;
  char const *string = va_arg(*args, char const *);

  size_t len = self->len = strlen(string);
  size_t capacity = self->capacity = next_pow_of_two(len + 1);
  self->str = safe_calloc(capacity, sizeof(char));
  memcpy(self->str, string, len + 1);

  return self;
}
