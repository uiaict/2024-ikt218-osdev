#pragma once

#include "libc/stdbool.h"

char *itoa(int num, char* buffer, int base); // Convert integer to string
char *utoa(unsigned int num, char* buffer, int base); // Convert unsigned integer to string
int atoi(char *str); // Convert string to integer
void ftoa(float n, char* res, int afterpoint); // Convert float to string


