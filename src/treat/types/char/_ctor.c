#include "char.ih"

void *Char_ctor(void *_self, va_list *args) {
  TChar *self = _self;
  char character = va_arg(*args, int);
  self->character = character;
  return self;
}
