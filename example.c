#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hash_map/hash_map.h"

#include "treat/type/type.h"
#include "treat/trait/trait.h"
#include "treat/traits/inspect/inspect.h"

#include "treat/types/char/char.h"
#include "treat/types/integer/integer.h"


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

void destroy(void *obj) {
  const Type **type_pointer = obj;
  if(obj && *type_pointer && (*type_pointer)->dtor)
    obj = (* type_pointer)->dtor(obj);
  free(obj);
}

/* typedef struct { */
/*   TypeRef typeref; */
/*   int integer; */
/* } TInteger; */

/* TInteger *Integer_new(int integer); */
/* void *Integer_ctor(void *self, va_list *args); */
/* void *Integer_dtor(void *self); */

/* void Integer_destroy(TInteger *integer); */

/* struct { */
/*   Type type; */
/*   TInteger *(*new)(int integer); */
/*   void(*destroy)(TInteger *integer); */
/* } Integer = { */
/*   .type.size = sizeof(TInteger), */
/*   .type.ctor = &Integer_ctor, */
/*   .type.dtor = &Integer_dtor, */

/*   .new = &Integer_new, */
/*   .destroy = &Integer_destroy */
/* }; */

/* void *Integer_ctor(void *_self, va_list *args) { */
/*   TInteger *self = _self; */
/*   int integer = va_arg(*args, int); */
/*   self->integer = integer; */
/*   return self; */
/* } */

/* void *Integer_dtor(void *_self) { */
/*   TInteger *self = _self; */
/*   // no-op */
/*   return self; */
/* } */

/* TInteger *Integer_new(int integer) { */
/*   TInteger *obj = new(&Integer, integer); */
/*   obj->integer = integer; */

/*   return obj; */
/* } */

/* void Integer_destroy(TInteger *integer) { */
/*   destroy(integer); */
/* } */

/* void Inspect_TInteger_inspect(void *obj_ptr) { */
/*   TInteger *obj = (TInteger *) obj_ptr; */
/*   printf("TInteger: {integer: %d}\n", obj->integer); */
/* } */


/* InspectTraitImplementation InspectTIntegerImplementation = { */
/*   .inspect = &Inspect_TInteger_inspect */
/* }; */

void initialize_trait_implementations(){
  Inspect.trait.implementations = HashMap_new(2);
  /* HashMap_insert(&Inspect.trait.implementations, &Char, &InspectTCharImplementation); */
  /* HashMap_insert(&Inspect.trait.implementations, &Integer, &InspectTIntegerImplementation); */
  Trait.add_impl(&Inspect, &Char, &Char_TraitImpls_Inspect);
  Trait.add_impl(&Inspect, &Integer, &Integer_TraitImpls_Inspect);
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
  Char.destroy(foo);
  Integer.destroy(bar);

  free_trait_implementations();
}
