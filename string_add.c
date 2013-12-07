#include "string_add.h"
#include <stdio.h>
char* string_add(char* left, char* right) {
  int leftlen = (int) *(left-4);
  int rightlen = (int) *(left-4);
  // 5 for 4 (preceding length field) + 1 (null terminator)
  char* s = (char*) malloc(5 + leftlen + rightlen);
  *((int*) s) = leftlen + rightlen;
  s += 4;
  int i = 0;
  for (i = 0; i < leftlen; i ++) {
    s[i] = left[i];
  }

  for (i = leftlen; i < leftlen + rightlen; i++) {
    s[i] = right[i-leftlen];
  }
  s[i] = '\0';

  return s;
}
