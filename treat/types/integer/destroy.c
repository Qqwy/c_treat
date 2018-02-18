#include "integer.ih"

void destroy(void *obj);
void Integer_destroy(TInteger *integer) {
  Treat.destroy(integer);
}
