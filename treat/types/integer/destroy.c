#include "integer.ih"

void destroy(void *obj);
void Integer_destroy(TInteger *integer) {
  destroy(integer);
}
