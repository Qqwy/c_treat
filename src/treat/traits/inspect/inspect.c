#include "inspect.ih"

void Inspect_inspect(void *_obj) {
  TypeRef * obj = (TypeRef *) _obj;
  void *_res = Trait.impl_for(&Inspect, obj->type);
  InspectTraitImplementation *res = _res;
  /* void (*res)(void *) = _res; */
  res->inspect(obj);
}
