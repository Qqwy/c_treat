#ifndef TREAT_TRAIT_H_
#define TREAT_TRAIT_H_

#include "../type/type.h"

struct _TraitStruct {
  void (*add_impl)(void *trait, void *type, void *impl);
  void *(*impl_for)(void const *trait, Type *type);
};

extern struct _TraitStruct const Trait;

#endif //TREAT_TRAIT_H_
