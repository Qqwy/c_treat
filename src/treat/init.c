#include "treat.ih"

#include "traits/inspect/inspect.h"
#include "types/char/char.h"
#include "types/string/string.h"
#include "types/integer/integer.h"

void Treat_deinit();
void Treat_init() {
  Inspect.trait.implementations = HashMap_new(2);
  Trait.add_impl(&Inspect, &Char, &Char_TraitImpls_Inspect);
  Trait.add_impl(&Inspect, &String, &String_TraitImpls_Inspect);
  Trait.add_impl(&Inspect, &Integer, &Integer_TraitImpls_Inspect);

  atexit(&Treat_deinit);
}

void Treat_deinit() {
    HashMap_destroy(Inspect.trait.implementations);
}
