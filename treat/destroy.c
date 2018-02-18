#include "treat.ih"

void Treat_destroy(void *obj) {
  const Type **type_pointer = obj;
  if(obj && *type_pointer && (*type_pointer)->dtor)
    obj = (* type_pointer)->dtor(obj);
  free(obj);
}
