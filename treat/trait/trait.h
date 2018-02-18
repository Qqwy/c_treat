#ifndef TREAT_TRAIT_H_
#define TREAT_TRAIT_H_

#include "../type/type.h"

// Module Interface:
struct _TreatTraitModule {
  void (*add_impl)(void *trait, void *type, void *impl);
  void *(*impl_for)(void const *trait, Type *type);
};
extern struct _TreatTraitModule const Trait;

#endif //TREAT_TRAIT_H_
