#pragma once
#include "libc/stdint.h"
#include "libc/stdbool.h"

#define EOF (-1)

int putchar(int ic);
bool print(const char* data, size_t length);
int printf(const char* __restrict__ format, ...);
void sprintf(char* str, const char* format, ...);


