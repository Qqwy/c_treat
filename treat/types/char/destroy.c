#include "char.ih"

void destroy(void *obj);
void Char_destroy(TChar *character) {
  Treat.destroy(character);
}
