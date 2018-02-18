#include "trait.ih"

struct _TreatTraitModule const Trait = {
  .add_impl = &Trait_add_impl,
  .impl_for = &Trait_impl_for,
};
