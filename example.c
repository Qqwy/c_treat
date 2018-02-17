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

void *Trait_impl_for(void const *trait, Type *type);

struct {
  void *(*impl_for)(void const *trait, Type *type);
} Trait = {
  .impl_for = &Trait_impl_for
};

void *Trait_impl_for(void const *_trait, Type * type) {
  TraitType trait = *(TraitType*)(_trait);
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

typedef struct {
  void (*inspect)(void *);
} InspectTraitImplementation;


void Inspect_inspect(void *_obj) {
  TypeRef * obj = (TypeRef *) _obj;
  void *_res = Trait.impl_for(&Inspect, obj->typeref);
  InspectTraitImplementation *res = _res;
  /* void (*res)(void *) = _res; */
  res->inspect(obj);
}

typedef struct {
  TypeRef typeref;
  char character;
} TChar;

TChar *Char_new(char character);

/* Type Char = {}; */
struct {
  Type type;
  TChar *(*new)(char character);
} Char = {
  .type = {},
  .new = &Char_new
};


TChar *Char_new(char character) {
  TChar *obj = calloc(1, sizeof(TChar));
  obj->typeref.typeref = &Char;
  obj->character = character;

  return obj;
}

void Inspect_TChar_inspect(void *obj_ptr) {
  TChar *obj = (TChar *) obj_ptr;
  printf("TChar: {character: %c}\n", obj->character);
}

InspectTraitImplementation InspectTCharImplementation = {
  .inspect = &Inspect_TChar_inspect
};

void initialize_trait_implementations(){
  Inspect.trait.implementations = HashMap_new(2);
  HashMap_insert(&Inspect.trait.implementations, &Char, &InspectTCharImplementation);
}

void free_trait_implementations(){
  HashMap_destroy(Inspect.trait.implementations);
}

int main(void) {
  initialize_trait_implementations();

  TChar *foo = Char.new('a');
  /* TChar * foo = calloc(1, sizeof(TChar)); */
  /* foo->typeref.typeref = &Char; */
  /* foo->character = 'a'; */
  /* InspectTCharImplementation.inspect(foo); */
  /* void (*res)(void *) = HashMap_lookup(Inspect.trait.implementations, foo->type.typeref); */
  /* res(foo); */
  Inspect.inspect(foo);
  free(foo);

  free_trait_implementations();
}
