#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t nstrlen(char* s);
int32_t fact(int32_t x, int32_t* p);
char* initLabel();
int32_t globalInt;
int32_t main() {
int32_t x;
x = 1;
int32_t y;
int32_t temp_0 = 2 * x;
int32_t temp_1 = temp_0 + 1;
y = temp_1;
int32_t z;
char* label;
char* temp_2 = initLabel();
char *temp_3 = (char *)malloc(5 + strlen(temp_2));
*((int*) temp_3) = strlen(temp_2);
temp_3 += 4;
strcpy(temp_3, temp_2);
label = temp_3;
int32_t* p;
printf ("%d\n", globalInt);
int32_t temp_4 = x * y;
int32_t temp_5 = y + temp_4;
int32_t* temp_6 = &globalInt;
p = temp_6;
int32_t temp_7 = fact(y, p);
printf ("%d\n", temp_7);
int32_t temp_8 = temp_5 + temp_7;
z = temp_8;
char *temp_9 = (char *)malloc(5 + strlen(" = "));
*((int*) temp_9) = strlen(" = ");
temp_9 += 4;
strcpy(temp_9, " = ");
char* temp_10 = string_add(label, temp_9);
char *temp_11 = (char *)malloc(5 + strlen(temp_10));
*((int*) temp_11) = strlen(temp_10);
temp_11 += 4;
strcpy(temp_11, temp_10);
label = temp_11;
char *temp_12 = (char *)malloc(5 + strlen("%s %d\n"));
*((int*) temp_12) = strlen("%s %d\n");
temp_12 += 4;
strcpy(temp_12, "%s %d\n");
char *temp_13 = (char *)malloc(5 + strlen(label));
*((int*) temp_13) = strlen(label);
temp_13 += 4;
strcpy(temp_13, label);
int32_t temp_14 = printf(temp_12, temp_13, z);
char *temp_15 = (char *)malloc(5 + strlen("The label '%s' has length %d\n"));
*((int*) temp_15) = strlen("The label '%s' has length %d\n");
temp_15 += 4;
strcpy(temp_15, "The label '%s' has length %d\n");
int32_t temp_16 = nstrlen(label);
char *temp_17 = (char *)malloc(5 + strlen(label));
*((int*) temp_17) = strlen(label);
temp_17 += 4;
strcpy(temp_17, label);
int32_t temp_18 = printf(temp_15, temp_17, temp_16);
char *temp_19 = (char *)malloc(5 + strlen("globalInt = %d\n"));
*((int*) temp_19) = strlen("globalInt = %d\n");
temp_19 += 4;
strcpy(temp_19, "globalInt = %d\n");
int32_t temp_20 = printf(temp_19, *p);
return 0;
}
