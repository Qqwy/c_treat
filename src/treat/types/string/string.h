#ifndef TREAT_TYPES_STRING_H_
#define TREAT_TYPES_STRING_H_

#include "../../type/type.h"

// Data Structure:
typedef struct {
  TypeRef typeref;
  char *str;
  size_t len;
  size_t capacity;
} TString;

// Module Interface:
struct _TreatTypesStringModule {
  Type type;
  // String.new(string str) creates a new String structure.
  TString *(*new)(char const* str);
  // String.destroy(TString string) frees a previously created String structure.
  void (*destroy)(TString *str);
  TString *(*concat_charptr)(TString *left, char const *right);
  TString *(*concat)(TString *left, TString const *right);
};
struct _TreatTypesStringModule String;

// Implemented Traits:
#include "../../traits/inspect/inspect.h"
InspectTraitImplementation String_TraitImpls_Inspect;

#endif //TREAT_TYPES_STRING_H
