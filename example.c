#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hash_map/hash_map.h"

#include "treat/type/type.h"
#include "treat/trait/trait.h"
#include "treat/traits/inspect/inspect.h"

#include "treat/types/char/char.h"
#include "treat/types/integer/integer.h"

void initialize_trait_implementations() {
  Inspect.trait.implementations = HashMap_new(2);
  Trait.add_impl(&Inspect, &Char, &Char_TraitImpls_Inspect);
  Trait.add_impl(&Inspect, &Integer, &Integer_TraitImpls_Inspect);
}

void free_trait_implementations() {
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
