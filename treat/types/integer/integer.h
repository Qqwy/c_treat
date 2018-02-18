#ifndef TREAT_TYPES_INTEGER_H_
#define TREAT_TYPES_INTEGER_H_

#include "../../type/type.h"

// Data Structure:
typedef struct {
  TypeRef typeref;
  int integer;
} TInteger;

// Module Interface:
struct _TreatTypesIntegerModule {
  Type type;
  // Integer.new(int integer) creates a new Integer structure.
  TInteger *(*new)(int integer);
  // Integer.destroy(TInteger integer) frees a previously created Integer structure.
  void(*destroy)(TInteger *integer);
};
struct _TreatTypesIntegerModule Integer;


// Implemented Traits:
#include "../../traits/inspect/inspect.h"
InspectTraitImplementation Integer_TraitImpls_Inspect;

#endif //TREAT_TYPES_INTEGER_H_
