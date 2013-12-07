#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t fact(int32_t x, int32_t* p);
char* initLabel();
int32_t globalInt;
char* initLabel() {
char* result;
char* temp_0;
if (1) {
char *temp_1 = (char *)malloc(5 + strlen("Result"));
*((int*) temp_1) = strlen("Result");
temp_1 += 4;
strcpy(temp_1, "Result");
temp_0 = temp_1;
} else {
char *temp_2 = (char *)malloc(5 + strlen("1 is false!"));
*((int*) temp_2) = strlen("1 is false!");
temp_2 += 4;
strcpy(temp_2, "1 is false!");
temp_0 = temp_2;
}
char *temp_3 = (char *)malloc(5 + strlen(temp_0));
*((int*) temp_3) = strlen(temp_0);
temp_3 += 4;
strcpy(temp_3, temp_0);
result = temp_3;
return result;
}
