#include "integer.ih"

struct _TreatTypesIntegerModule Integer = {
  .type.size = sizeof(TInteger),
  .type.name = "Integer",
  .type.ctor = &Integer_ctor,
  .type.dtor = &Integer_dtor,

  .new = &Integer_new,
  .destroy = &Integer_destroy
};
