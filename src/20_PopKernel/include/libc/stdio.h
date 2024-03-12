#pragma once
#include "libc/stdint.h"
#include "libc/stdbool.h"

#define EOF (-1)

int putchar(int ic);                                // Print a character        
bool print(const char* data, size_t length);        // Print a string of characters
int printf(const char* __restrict__ format, ...);   // Print a formatted string
char getchar();                                     // Get a character from the keyboard
void scanf(const char* __restrict__ format, ...);   // Get a formatted string from the keyboard
int isspace(int c);                                 // Check if a character is a space


