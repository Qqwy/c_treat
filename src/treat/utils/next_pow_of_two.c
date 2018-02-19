#include "math.h"

size_t next_pow_of_two(size_t num) {
  size_t power = 1;
  do
    power*=2;
  while (power < num);
  return power;
}
