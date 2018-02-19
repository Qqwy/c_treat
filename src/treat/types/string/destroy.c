#include "string.ih"

void String_destroy(TString *string) {
  Treat.destroy(string);
}
