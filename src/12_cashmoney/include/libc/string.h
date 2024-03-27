#pragma once

#include <libc/stdint.h>

// String length of null terminated strings
size_t string_length(const char *c_str);

// String copy, does not check if src fits into dest
void string_copy(char *dest, const char *src);

// String copy, does check if src fits into dest
void string_copy_safe(char *dest, size_t destSize, const char *src, size_t srcSize);