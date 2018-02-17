#include <stdlib.h>
#include <stdio.h>

#include "hash_map/hash_map.h"

typedef struct {} Type;

typedef struct {
  void *typeref;
} TypeRef;

typedef struct {
  HashMap *implementations;
} TraitType;

void *Trait_impl_for(TraitType const trait, Type *type);

struct {
  void *(*impl_for)(TraitType const, Type *);
} Trait = {
  .impl_for = &Trait_impl_for
};

void *Trait_impl_for(TraitType const trait, Type * type) {
  return HashMap_lookup(trait.implementations, type);
}

void Inspect_inspect(void *obj);

struct {
  TraitType trait;
  void (*inspect)(void *);
} Inspect = {
  .trait ={},
  .inspect = &Inspect_inspect
};


void Inspect_inspect(void *_obj) {
  TypeRef* obj = (TypeRef *) _obj;
  /* void (*res)(void *) = HashMap_lookup(Inspect.trait.implementations, ((TypeRef*) obj)->typeref); */
  void *_res = Trait.impl_for((Inspect.trait), obj->typeref);
  void (*res)(void *) = _res;
  res(obj);
}

typedef struct {
  void (*inspect)(void *);
} InspectTraitImplementation;

Type Char = {};
typedef struct {
  TypeRef typeref;
  char character;
} TChar;


void TChar_Inspect_inspect(void *obj_ptr) {
  TChar *obj = (TChar *) obj_ptr;
  printf("TChar: {character: %c}\n", obj->character);
}

InspectTraitImplementation TCharInspectImplementation = {
  .inspect = &TChar_Inspect_inspect
};

void initialize_trait_implementations(){
  Inspect.trait.implementations = HashMap_new(2);
  HashMap_insert(&Inspect.trait.implementations, &Char, TChar_Inspect_inspect);
}

void free_trait_implementations(){
  HashMap_destroy(Inspect.trait.implementations);
}

int main(void) {
  initialize_trait_implementations();

  TChar * foo = calloc(1, sizeof(TChar));
  foo->typeref.typeref = &Char;
  foo->character = 'a';
  /* TCharInspectImplementation.inspect(foo); */
  /* void (*res)(void *) = HashMap_lookup(Inspect.trait.implementations, foo->type.typeref); */
  /* res(foo); */
  Inspect.inspect(foo);
  free(foo);

  free_trait_implementations();
}
