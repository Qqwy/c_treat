#include "string.ih"

#include <stdio.h>

void *String_dtor(void *_self) {
  TString *self = _self;

  free(self->str);

  return self;
}
