#include "string.ih"

void destroy(void *obj);
void String_destroy(TString *string) {
  Treat.destroy(string);
}
