#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "hash_map/hash_map.h"

#include "treat/treat.h"

#include "treat/types/char/char.h"
#include "treat/types/integer/integer.h"
#include "treat/with.macro"



int main(void) {
  Treat.init();

  /* TInteger *foo, *bar = Integer.new(123); */

  T_with(TChar * baz, Char.new('b'), {
    Inspect.inspect(baz);
    Inspect.inspect(baz);

    TChar *foo = Char.new('a');
    TInteger *bar = Integer.new(1234);
    Inspect.inspect(foo);
    Inspect.inspect(bar);
    Char.destroy(foo);
    Integer.destroy(bar);



    T_with(TInteger * my_int, Integer.new(1235), {
        Inspect.inspect(my_int);
    });
  });
}
