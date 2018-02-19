#include "../integer.ih"
#include "../../../traits/inspect/inspect.h"

#include <stdio.h>

void Integer_TraitImpls_Inspect_inspect(void *obj_ptr) {
  TInteger *obj = (TInteger *) obj_ptr;
  printf("TInteger: {integer: %d}\n", obj->integer);
}

InspectTraitImplementation Integer_TraitImpls_Inspect = {
  .inspect = &Integer_TraitImpls_Inspect_inspect
};
