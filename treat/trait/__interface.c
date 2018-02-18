#include "trait.ih"

struct _TraitStruct const Trait = {
  .add_impl = &Trait_add_impl,
  .impl_for = &Trait_impl_for,
};
