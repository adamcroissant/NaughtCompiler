#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t main() {
char* s;
char *temp_0 = (char *)malloc(5 + strlen("a"));
*((int*) temp_0) = strlen("a");
temp_0 += 4;
strcpy(temp_0, "a");
char *temp_1 = (char *)malloc(5 + strlen(temp_0));
*((int*) temp_1) = strlen(temp_0);
temp_1 += 4;
strcpy(temp_1, temp_0);
s = temp_1;
int32_t x;
x = 1;
