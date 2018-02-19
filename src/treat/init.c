#include "treat.ih"

#include "traits/inspect/inspect.h"
#include "types/char/char.h"
#include "types/string/string.h"
#include "types/integer/integer.h"

#include <stdarg.h>


void Treat_deinit();
void Treat_init(size_t n_impls, ...) {
  Inspect.trait.implementations = HashMap_new(2);
  Trait.add_impl(&Inspect, &Char, &Char_TraitImpls_Inspect);
  Trait.add_impl(&Inspect, &String, &String_TraitImpls_Inspect);

  atexit(&Treat_deinit);

  va_list(args);
  va_start(args, n_impls);
  for(size_t impl_index = 0; impl_index < n_impls; ++impl_index) {
    struct _TraitImplementationTriple foo;
    foo = va_arg(args, struct _TraitImplementationTriple);
    Trait.add_impl(foo.trait, foo.type, foo.impl_struct);
  }
  va_end(args);
}

void Treat_deinit() {
    HashMap_destroy(Inspect.trait.implementations);
}
