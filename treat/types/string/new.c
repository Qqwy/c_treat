#include "string.ih"

TString *String_new(char const *str) {
  TString *obj = Treat.new(&String, str);
  return obj;
}