#pragma once
#include "libc/stdint.h"

size_t strlen(char *str);               // Get the length of a string
char *strchr(char *str, int c);         // Get the first occurrence of a character in a string
void strrev(char str[], int length);    // Reverse a string

