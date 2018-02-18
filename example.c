#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hash_map/hash_map.h"

typedef struct {
  size_t size;
  void *(*ctor)(void *self, va_list *arguments);
  void *(*dtor)(void *self);
} Type;

typedef struct {
  void *type;
} TypeRef;

typedef struct {
  HashMap *implementations;
} TraitType;

void Trait_add_impl(void *trait, void *type, void *impl);
void *Trait_impl_for(void const *trait, Type *type);

struct {
  void (*add_impl)(void *trait, void *type, void *impl);
  void *(*impl_for)(void const *trait, Type *type);
} Trait = {
  .add_impl = &Trait_add_impl,
  .impl_for = &Trait_impl_for,
};


void Trait_add_impl(void *_trait, void *_type, void *impl){
  Type *type = _type;
  TraitType *trait = _trait;
  HashMap_insert(&trait->implementations, type, impl);
}

void *Trait_impl_for(void const *_trait, Type *type) {
  TraitType trait = *(TraitType*)(_trait);
  void * trait_impl = HashMap_lookup(trait.implementations, type);
  if(trait_impl == NULL) {
    printf("Error in Trait implementation lookup. Trait might not be implemented for type.\n");
  }
  return trait_impl;
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
  void *_res = Trait.impl_for(&Inspect, obj->type);
  InspectTraitImplementation *res = _res;
  /* void (*res)(void *) = _res; */
  res->inspect(obj);
}

typedef struct {
  TypeRef typeref;
  char character;
} TChar;

TChar *Char_new(char character);
void *Char_ctor(void *self, va_list *args);
void *Char_dtor(void *self);

struct {
  Type type;
  TChar *(*new)(char character);
} Char = {
  .type.size = sizeof(TChar),
  .type.ctor = &Char_ctor,
  .type.dtor = &Char_dtor,

  .new = &Char_new
};

void *Char_ctor(void *_self, va_list *args) {
  TChar *self = _self;
  char character = va_arg(*args, int);
  self->character = character;
  return self;
}

void *Char_dtor(void *_self) {
  TChar *self = _self;
  // no-op
  return self;
}


void *new(const void * _type, ...) {
  const Type *type = _type;
  void *obj = calloc(1, type->size);
  /* assert(obj); */

  *(const Type **) obj = type;
  if(type->ctor) {
    va_list args;
    va_start(args, _type);
    obj = type->ctor(obj, &args);
    va_end(args);
  }
  return obj;
}

TChar *Char_new(char character) {
  TChar *obj = new(&Char, character);
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


typedef struct {
  TypeRef typeref;
  int integer;
} TInteger;

TInteger *Integer_new(int integer);
void *Integer_ctor(void *self, va_list *args);
void *Integer_dtor(void *self);

struct {
  Type type;
  TInteger *(*new)(int integer);
} Integer = {
  .type.size = sizeof(TInteger),
  .type.ctor = &Integer_ctor,
  .type.dtor = &Integer_dtor,

  .new = &Integer_new
};

void *Integer_ctor(void *_self, va_list *args) {
  TInteger *self = _self;
  int integer = va_arg(*args, int);
  self->integer = integer;
  return self;
}

void *Integer_dtor(void *_self) {
  TInteger *self = _self;
  // no-op
  return self;
}

TInteger *Integer_new(int integer) {
  TInteger *obj = new(&Integer, integer);
  obj->integer = integer;

  return obj;
}

void Inspect_TInteger_inspect(void *obj_ptr) {
  TInteger *obj = (TInteger *) obj_ptr;
  printf("TInteger: {integer: %d}\n", obj->integer);
}


InspectTraitImplementation InspectTIntegerImplementation = {
  .inspect = &Inspect_TInteger_inspect
};



void initialize_trait_implementations(){
  Inspect.trait.implementations = HashMap_new(2);
  /* HashMap_insert(&Inspect.trait.implementations, &Char, &InspectTCharImplementation); */
  /* HashMap_insert(&Inspect.trait.implementations, &Integer, &InspectTIntegerImplementation); */
  Trait.add_impl(&Inspect, &Char, &InspectTCharImplementation);
  Trait.add_impl(&Inspect, &Integer, &InspectTIntegerImplementation);
}

void free_trait_implementations(){
  HashMap_destroy(Inspect.trait.implementations);
}

int main(void) {
  initialize_trait_implementations();

  TChar *foo = Char.new('a');
  TInteger *bar = Integer.new(1234);
  Inspect.inspect(foo);
  Inspect.inspect(bar);
  free(foo);
  free(bar);
  free_trait_implementations();
}
