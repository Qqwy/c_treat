#include "string.ih"

TString *String_concat(TString *left, TString const *right){
  size_t new_len = left->len + right->len;

  if(left->capacity < new_len + 1) {
    left->capacity = next_pow_of_two(new_len + 1);
    left->str = safe_realloc(left->str, left->capacity);
  }
  memcpy(left->str + left->len, right->str, right->len + 1);
  left->len = new_len;
  return left;
}
