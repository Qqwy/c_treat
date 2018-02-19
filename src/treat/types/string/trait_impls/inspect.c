#include "../string.ih"
#include "../../../traits/inspect/inspect.h"

#include <stdio.h>

void String_TraitImpls_Inspect_inspect(void *obj_ptr) {
  TString *obj = (TString *) obj_ptr;
  printf("TString: {str: \"%s\"}\n", obj->str);
}

InspectTraitImplementation String_TraitImpls_Inspect = {
  .inspect = &String_TraitImpls_Inspect_inspect
};
