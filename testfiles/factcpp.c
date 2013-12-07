#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t fact(int32_t x, int32_t* p);
char* initLabel();
int32_t globalInt;
int32_t fact(int32_t x, int32_t* p) {
printf ("%d\n", x);
int32_t temp_0;
if (x) {
int32_t temp_1 = x - 1;
int32_t temp_2 = fact(temp_1, p);
int32_t temp_3 = x * temp_2;
temp_0 = temp_3;
} else {
temp_0 = 1;
}
*p = temp_0;
return *p;
}
