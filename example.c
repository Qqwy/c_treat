#include <stdlib.h>
#include <stdio.h>

#include "hash_map/hash_map.h"

typedef struct {
  void *typeref;
} Type;

typedef struct {
  HashMap *implementations;
} Trait;

void Inspect_inspect(void *obj);

struct {
  Trait trait;
  void (*inspect)(void *);
} Inspect  = {
  .trait ={},
  .inspect = &Inspect_inspect
};


void Inspect_inspect(void *obj) {
  void (*res)(void *) = HashMap_lookup(Inspect.trait.implementations, ((Type*) obj)->typeref);
  res(obj);
}

typedef struct {
  void (*inspect)(void *);
} InspectTraitImplementation;

struct {} Char = {};
typedef struct {
  Type type;
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
  foo->type.typeref = &Char;
  foo->character = 'a';
  /* TCharInspectImplementation.inspect(foo); */
  /* void (*res)(void *) = HashMap_lookup(Inspect.trait.implementations, foo->type.typeref); */
  /* res(foo); */
  Inspect.inspect(foo);
  free(foo);

  free_trait_implementations();
}
