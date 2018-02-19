#include "string.ih"

TString *String_concat_charptr(TString *left, char const *right){
  size_t right_len = strlen(right);
  size_t new_len = left->len + right_len;

  if(left->capacity < new_len + 1) {
    left->capacity = next_pow_of_two(new_len + 1);
    left->str = safe_realloc(left->str, left->capacity);
  }
  memcpy(left->str + left->len, right, right_len + 1);
  left->len = new_len;
  return left;
}
