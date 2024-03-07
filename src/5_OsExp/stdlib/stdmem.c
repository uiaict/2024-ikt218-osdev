#include "stdmem.h"

void *memCopy(void *tar, const void *src, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        ((unsigned char *) tar)[i] = ((unsigned char *) src)[i]; // Copy from source to target.
    }

    return tar;
}

void *memSet(void *string, int c, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        ((unsigned char *) string)[i] = c; // Simply assign the given input to every element of the string.
    }
    
    return string;
}
