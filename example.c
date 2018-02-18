#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hash_map/hash_map.h"

#include "treat/treat.h"
#include "treat/type/type.h"
#include "treat/trait/trait.h"
#include "treat/traits/inspect/inspect.h"

#include "treat/types/char/char.h"
#include "treat/types/integer/integer.h"

int main(void) {
  Treat.init();

  TChar *foo = Char.new('a');
  TInteger *bar = Integer.new(1234);
  Inspect.inspect(foo);
  Inspect.inspect(bar);
  Char.destroy(foo);
  Integer.destroy(bar);

}
