#include "integer.ih"

void Integer_destroy(TInteger *integer) {
  Treat.destroy(integer);
}
