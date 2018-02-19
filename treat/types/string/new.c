#include "string.ih"

TString *String_new(char *str) {
  TString *obj = Treat.new(&String, str);
  return obj;
}
