#include "char.ih"

void *new(const void * _type, ...);
TChar *Char_new(char character) {
  TChar *obj = new(&Char, character);
  obj->character = character;

  return obj;
}
