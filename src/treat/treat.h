#ifndef TREAT_H_
#define TREAT_H_

#include <sys/types.h>
#include "type/type.h"

struct _TraitImplementationTriple {
  TraitType * trait;
  Type * type;
  void * impl_struct;
};

struct _TreatModule {
  void *(*new)(const void * type, ...);
  void (*destroy)(void *obj);
  void (*init)();
};
struct _TreatModule Treat;

#endif //TREAT_H_
