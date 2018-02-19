#ifndef TREAT_TYPES_CHAR_H_
#define TREAT_TYPES_CHAR_H_

#include "../../type/type.h"

// Data Structure:
typedef struct {
  TypeRef typeref;
  char character;
} TChar;

// Module Interface:
struct _TreatTypesCharModule {
  Type type;
  // Char.new(char character) creates a new Char structure.
  TChar *(*new)(char character);
  // Char.destroy(TChar char) frees a previously created Char structure.
  void (*destroy)(TChar *character);
};
struct _TreatTypesCharModule Char;

// Implemented Traits:
#include "../../traits/inspect/inspect.h"
InspectTraitImplementation Char_TraitImpls_Inspect;

#endif //TREAT_TYPES_CHAR_H
