#include "trait.ih"

void Trait_add_impl(void *_trait, void *_type, void *impl){
  Type *type = _type;
  TraitType *trait = _trait;
  HashMap_insert(&trait->implementations, type, impl);
}
