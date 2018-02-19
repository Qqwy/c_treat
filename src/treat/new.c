#include "treat.ih"

void *Treat_new(const void * _type, ...) {
  const Type *type = _type;
  void *obj = safe_calloc(1, type->size);
  /* assert(obj); */

  *(const Type **) obj = type;
  if(type->ctor) {
    va_list args;
    va_start(args, _type);
    obj = type->ctor(obj, &args);
    va_end(args);
  }
  return obj;
}
