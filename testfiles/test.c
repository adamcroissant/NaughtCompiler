#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t testfunc1(int32_t x, int32_t y);
char* testfunc2(char* s, int32_t* p);
int32_t globalOne;
int32_t testingInts2(int32_t y) {
printf ("%d\n", y);
}
int32_t testingInts(int32_t x) {
printf ("%d\n", x);
char *temp_0 = (char *)malloc(5 + strlen("%s%d\n"));
*((int*) temp_0) = strlen("%s%d\n");
temp_0 += 4;
strcpy(temp_0, "%s%d\n");
char *temp_1 = (char *)malloc(5 + strlen("just printed the variable x: "));
*((int*) temp_1) = strlen("just printed the variable x: ");
temp_1 += 4;
strcpy(temp_1, "just printed the variable x: ");
int32_t temp_2 = printf(temp_0, temp_1, x);
int32_t temp_3 = x + 20;
x = temp_3;
printf ("%d\n", x);
int32_t temp_4 = x / 5;
x = temp_4;
printf ("%d\n", x);
x = 3;
int32_t temp_5 = x * x;
x = temp_5;
char *temp_6 = (char *)malloc(5 + strlen("%s%d\n"));
*((int*) temp_6) = strlen("%s%d\n");
temp_6 += 4;
strcpy(temp_6, "%s%d\n");
char *temp_7 = (char *)malloc(5 + strlen("3 squared = "));
*((int*) temp_7) = strlen("3 squared = ");
temp_7 += 4;
strcpy(temp_7, "3 squared = ");
int32_t temp_8 = printf(temp_6, temp_7, x);
int32_t temp_9 = x - 1;
x = temp_9;
printf ("%d\n", x);
int32_t temp_10 = testingInts2(x);
return x;
}
char* testingStrings(char* s1, char* s2) {
char* s4;
char* tmp;
int32_t x;
char *temp_11 = (char *)malloc(5 + strlen("s1 "));
*((int*) temp_11) = strlen("s1 ");
temp_11 += 4;
strcpy(temp_11, "s1 ");
char *temp_12 = (char *)malloc(5 + strlen(temp_11));
*((int*) temp_12) = strlen(temp_11);
temp_12 += 4;
strcpy(temp_12, temp_11);
s1 = temp_12;
char *temp_13 = (char *)malloc(5 + strlen("s2 "));
*((int*) temp_13) = strlen("s2 ");
temp_13 += 4;
strcpy(temp_13, "s2 ");
char *temp_14 = (char *)malloc(5 + strlen(temp_13));
*((int*) temp_14) = strlen(temp_13);
temp_14 += 4;
strcpy(temp_14, temp_13);
s2 = temp_14;
char* temp_15 = string_add(s1, s2);
char *temp_16 = (char *)malloc(5 + strlen("s3"));
*((int*) temp_16) = strlen("s3");
temp_16 += 4;
strcpy(temp_16, "s3");
printf ("%s\n", temp_16);
char* temp_17 = string_add(temp_15, temp_16);
char *temp_18 = (char *)malloc(5 + strlen(temp_17));
*((int*) temp_18) = strlen(temp_17);
temp_18 += 4;
strcpy(temp_18, temp_17);
s4 = temp_18;
printf ("%s\n", s4);
x = 1;
char *temp_19 = (char *)malloc(5 + strlen("success"));
*((int*) temp_19) = strlen("success");
temp_19 += 4;
strcpy(temp_19, "success");
char *temp_20 = (char *)malloc(5 + strlen("failure"));
*((int*) temp_20) = strlen("failure");
temp_20 += 4;
strcpy(temp_20, "failure");
char* temp_21;
if (x) {
temp_21 = temp_19;
} else {
temp_21 = temp_20;
}
char *temp_22 = (char *)malloc(5 + strlen(temp_21));
*((int*) temp_22) = strlen(temp_21);
temp_22 += 4;
strcpy(temp_22, temp_21);
tmp = temp_22;
printf ("%s\n", tmp);
char *temp_23 = (char *)malloc(5 + strlen(" s5"));
*((int*) temp_23) = strlen(" s5");
temp_23 += 4;
strcpy(temp_23, " s5");
char* temp_24 = string_add(s4, temp_23);
return temp_24;
}
int32_t main() {
char* s1;
char *temp_25 = (char *)malloc(5 + strlen("testing string"));
*((int*) temp_25) = strlen("testing string");
temp_25 += 4;
strcpy(temp_25, "testing string");
char *temp_26 = (char *)malloc(5 + strlen(temp_25));
*((int*) temp_26) = strlen(temp_25);
temp_26 += 4;
strcpy(temp_26, temp_25);
s1 = temp_26;
printf ("%s\n", s1);
char *temp_27 = (char *)malloc(5 + strlen("testing literal"));
*((int*) temp_27) = strlen("testing literal");
temp_27 += 4;
strcpy(temp_27, "testing literal");
char* temp_28 = testingStrings(s1, temp_27);
printf ("%s\n", temp_28);
printf ("%s\n", s1);
int32_t temp_29 = nstrlen(s1);
printf ("%d\n", temp_29);
}
