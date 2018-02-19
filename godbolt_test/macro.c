/*
This is a test
to see how the  `T_with` macro behaves
when actually compiled.
using the `godbolt.io` Compiler Explorer
(permlink: https://godbolt.org/g/Wo8E5S)
 */

#include <stdio.h>
#include <stdlib.h>

#define TPimpl(x, y) x ## y
#define TP(x, y) TPimpl(x, y)


#define T_with(var_decl, init)                    \
  while(1)                                            \
    if(0)                                             \
    TP(__using_finished, __LINE__):                   \
      break;                                          \
    else                                              \
      for(void *_tmp = 0;;)                           \
        for(var_decl = _tmp = (init);;)           \
          if (0) {                                    \
          TP(__using_cleanup, __LINE__):              \
            destroy(_tmp);                      \
            goto TP(__using_finished, __LINE__);      \
          } else                                      \
            if (1) {                                  \
              goto TP(__using_body, __LINE__);        \
            } else                                    \
              while (1)                               \
                if (1){                               \
                  goto TP(__using_cleanup, __LINE__); \
                } else                                \
                TP(__using_body, __LINE__):           \

int *new(int val) {
    int *ptr = malloc(sizeof(int));
    *ptr = val;
    return ptr;
}

void destroy(int *ptr) {
    free(ptr);
}


// Type your code here, or load an example.
int square(int num) {
    return num * num;
}


int main(){
    int bar = 20;
    T_with(int *foo, new(bar)) {
        printf("Foo(%p) is:%d\n", foo, *foo);
    }
    printf("test\n");
}
