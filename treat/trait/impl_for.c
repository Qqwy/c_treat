#include "trait.ih"

void *Trait_impl_for(void const *_trait, Type *type) {
  TraitType trait = *(TraitType*)(_trait);
  void * trait_impl = HashMap_lookup(trait.implementations, type);
  if(trait_impl == NULL) {
    printerr("Error in Trait implementation lookup. Trait might not be implemented for type.\n");
  }
  return trait_impl;
}
