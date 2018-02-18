#include "../char.ih"
#include "../../../traits/inspect/inspect.h"

#include <stdio.h>

void Char_TraitImpls_Inspect_inspect(void *obj_ptr) {
  TChar *obj = (TChar *) obj_ptr;
  printf("TChar: {character: %c}\n", obj->character);
}

InspectTraitImplementation Char_TraitImpls_Inspect = {
  .inspect = &Char_TraitImpls_Inspect_inspect
};
