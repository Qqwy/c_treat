#include "trait.ih"

void *Trait_impl_for(void const *_trait, Type *type) {
  TraitType trait = *(TraitType*)(_trait);
  void * trait_impl = HashMap_lookup(trait.implementations, type);
  if(trait_impl == NULL) {
    printerr("Error in Trait implementation lookup. Trait %s might not be implemented for type %s.\n", trait.name, type->name);
  }
  return trait_impl;
}
