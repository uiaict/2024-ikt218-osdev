#include "stdmem.h"

void *memCopy(void *tar, const void *src, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        // uint16_t is important, previously used uint8_t which caused half the screen to be green.
        ((uint16_t *) tar)[i] = ((uint16_t *) src)[i]; // Copy from source to target.
    }

    return tar;
}

void *memSet(void *string, int c, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        // uint16_t is important, previously used uint8_t which caused half the screen to be green.
        ((uint16_t *) string)[i] = c; // Simply assign the given input to every element of the string.
    }
    
    return string;
}
