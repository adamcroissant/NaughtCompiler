#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t testptr(int32_t* p1) {
int32_t* p2;
p2 = p1;
int32_t temp_0 = *p2 + 1;
*p2 = temp_0;
}
int32_t main() {
int32_t x;
x = 5;
int32_t* p;
int32_t* temp_1 = &x;
p = temp_1;
printf ("%d\n", x);
int32_t temp_2 = testptr(p);
printf ("%d\n", x);
return 0;
}
