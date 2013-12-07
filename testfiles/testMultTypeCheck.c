#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t testMult() {
int32_t x;
x = 1;
char* s;
char *temp_0 = (char *)malloc(5 + strlen("s"));
*((int*) temp_0) = strlen("s");
temp_0 += 4;
strcpy(temp_0, "s");
char *temp_1 = (char *)malloc(5 + strlen(temp_0));
*((int*) temp_1) = strlen(temp_0);
temp_1 += 4;
strcpy(temp_1, temp_0);
s = temp_1;
int32_t temp_2 = x * 2;
