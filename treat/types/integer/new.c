#include "integer.ih"

void *new(const void * _type, ...);
TInteger *Integer_new(int integer) {
  TInteger *obj = Treat.new(&Integer, integer);
  obj->integer = integer;

  return obj;
}
