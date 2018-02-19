#include "string.ih"

void *String_ctor(void *_self, va_list *args) {
  TString *self = _self;
  char *string = va_arg(*args, char *);

  size_t len = self->len = strlen(string);
  self->str = safe_calloc(len + 1, sizeof(char));
  memcpy(self->str, string, len + 1) ;

  return self;
}
