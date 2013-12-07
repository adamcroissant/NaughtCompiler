#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_add.h"
int32_t nstrlen(char* s);
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
char *temp_2 = (char *)malloc(5 + strlen(temp_1));
*((int*) temp_2) = strlen(temp_1);
temp_2 += 4;
strcpy(temp_2, temp_1);
int32_t temp_3 = printf(temp_0, temp_2, x);
int32_t temp_4 = x + 20;
x = temp_4;
printf ("%d\n", x);
int32_t temp_5 = x / 5;
x = temp_5;
printf ("%d\n", x);
x = 3;
int32_t temp_6 = x * x;
x = temp_6;
char *temp_7 = (char *)malloc(5 + strlen("%s%d\n"));
*((int*) temp_7) = strlen("%s%d\n");
temp_7 += 4;
strcpy(temp_7, "%s%d\n");
char *temp_8 = (char *)malloc(5 + strlen("3 squared = "));
*((int*) temp_8) = strlen("3 squared = ");
temp_8 += 4;
strcpy(temp_8, "3 squared = ");
char *temp_9 = (char *)malloc(5 + strlen(temp_8));
*((int*) temp_9) = strlen(temp_8);
temp_9 += 4;
strcpy(temp_9, temp_8);
int32_t temp_10 = printf(temp_7, temp_9, x);
int32_t temp_11 = x - 1;
x = temp_11;
printf ("%d\n", x);
int32_t temp_12 = testingInts2(x);
return x;
}
int32_t testPtrs(int32_t* p1) {
int32_t* p2;
p2 = p1;
printf ("%d\n", *p1);
printf ("%d\n", *p2);
int32_t temp_13 = *p2 + 1;
*p2 = temp_13;
printf ("%d\n", *p2);
return *p2;
}
char* testingStrings(char* s1, char* s2) {
char* s4;
char* tmp;
int32_t x;
char *temp_14 = (char *)malloc(5 + strlen("s1 "));
*((int*) temp_14) = strlen("s1 ");
temp_14 += 4;
strcpy(temp_14, "s1 ");
char *temp_15 = (char *)malloc(5 + strlen(temp_14));
*((int*) temp_15) = strlen(temp_14);
temp_15 += 4;
strcpy(temp_15, temp_14);
s1 = temp_15;
char *temp_16 = (char *)malloc(5 + strlen("s2 "));
*((int*) temp_16) = strlen("s2 ");
temp_16 += 4;
strcpy(temp_16, "s2 ");
char *temp_17 = (char *)malloc(5 + strlen(temp_16));
*((int*) temp_17) = strlen(temp_16);
temp_17 += 4;
strcpy(temp_17, temp_16);
s2 = temp_17;
char* temp_18 = string_add(s1, s2);
char *temp_19 = (char *)malloc(5 + strlen("s3"));
*((int*) temp_19) = strlen("s3");
temp_19 += 4;
strcpy(temp_19, "s3");
printf ("%s\n", temp_19);
char* temp_20 = string_add(temp_18, temp_19);
char *temp_21 = (char *)malloc(5 + strlen(temp_20));
*((int*) temp_21) = strlen(temp_20);
temp_21 += 4;
strcpy(temp_21, temp_20);
s4 = temp_21;
printf ("%s\n", s4);
x = 1;
char* temp_22;
if (x) {
char *temp_23 = (char *)malloc(5 + strlen("success"));
*((int*) temp_23) = strlen("success");
temp_23 += 4;
strcpy(temp_23, "success");
temp_22 = temp_23;
} else {
char *temp_24 = (char *)malloc(5 + strlen("failure"));
*((int*) temp_24) = strlen("failure");
temp_24 += 4;
strcpy(temp_24, "failure");
temp_22 = temp_24;
}
char *temp_25 = (char *)malloc(5 + strlen(temp_22));
*((int*) temp_25) = strlen(temp_22);
temp_25 += 4;
strcpy(temp_25, temp_22);
tmp = temp_25;
printf ("%s\n", tmp);
char *temp_26 = (char *)malloc(5 + strlen(" s5"));
*((int*) temp_26) = strlen(" s5");
temp_26 += 4;
strcpy(temp_26, " s5");
char* temp_27 = string_add(s4, temp_26);
return temp_27;
}
int32_t main() {
char* s1;
char *temp_28 = (char *)malloc(5 + strlen("testing string"));
*((int*) temp_28) = strlen("testing string");
temp_28 += 4;
strcpy(temp_28, "testing string");
char *temp_29 = (char *)malloc(5 + strlen(temp_28));
*((int*) temp_29) = strlen(temp_28);
temp_29 += 4;
strcpy(temp_29, temp_28);
s1 = temp_29;
int32_t x;
printf ("%s\n", s1);
char *temp_30 = (char *)malloc(5 + strlen("testing literal"));
*((int*) temp_30) = strlen("testing literal");
temp_30 += 4;
strcpy(temp_30, "testing literal");
char *temp_31 = (char *)malloc(5 + strlen(temp_30));
*((int*) temp_31) = strlen(temp_30);
temp_31 += 4;
strcpy(temp_31, temp_30);
char* temp_32 = testingStrings(s1, temp_31);
printf ("%s\n", temp_32);
printf ("%s\n", s1);
int32_t temp_33 = nstrlen(s1);
printf ("%d\n", temp_33);
char *temp_34 = (char *)malloc(5 + strlen(""));
*((int*) temp_34) = strlen("");
temp_34 += 4;
strcpy(temp_34, "");
printf ("%s\n", temp_34);
x = 5;
printf ("%d\n", x);
int32_t* temp_35 = &x;
int32_t temp_36 = testPtrs(temp_35);
printf ("%d\n", x);
}
