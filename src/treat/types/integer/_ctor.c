#include "integer.ih"

void *Integer_ctor(void *_self, va_list *args) {
  TInteger *self = _self;
  int integer = va_arg(*args, int);
  self->integer = integer;
  return self;
}
