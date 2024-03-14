#pragma once

#include "stdarg.h" // for va_list
#include "string.h" // for strlen
#include "stdint.h" // for size_t
#include "stdbool.h" // for bool

//Defining End Of File, to use in printf: Should be defined in a global variables header file (coming soon?)
#ifndef EOF
#define EOF (-1)
#endif


// Function prints a character to the terminal using vga text mode buffer, called by printf
int putchar(int ic);

// Function could print a string to the terminal using vga text mode buffer
// but printf already does this, so its not very useful considering the size of our project and what we print
bool print(const char* data, size_t length);

// Creating an extern "C" block to prevent name mangling, which breaks the linker to .c files such as kernel.c
// Allowing us to use printf in .c files
#ifdef __cplusplus
extern "C" {
#endif
// Function prints a string using putchar, taking a string, 
// and arguments used if it includes format specifiers: Should also update the cursor position (coming later)
int printf(const char* __restrict__ format, ...);

#ifdef __cplusplus
}
#endif