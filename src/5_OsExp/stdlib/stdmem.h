#include "stdint.h"

// Copy a chunk of memory from one buffer to another.
void *memCopy(void *tar, const void *src, size_t n);

// Set the values in a buffer.
void *memSet(void *string, int character, size_t n);