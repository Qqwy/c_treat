#include "integer.ih"

void *new(const void * _type, ...);
TInteger *Integer_new(int integer) {
  TInteger *obj = new(&Integer, integer);
  obj->integer = integer;

  return obj;
}
