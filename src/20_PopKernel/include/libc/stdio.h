#pragma once
#include "libc/stdint.h"
#include "libc/stdbool.h"

#define EOF (-1)

int putchar(int ic);                                // Print a character        
bool print(const char* data, size_t length);        // Print a string of characters
int printf(const char* __restrict__ format, ...);   // Print a formatted string
void sprintf(char* str, const char* format, ...);   // Print a formatted string to a buffer


