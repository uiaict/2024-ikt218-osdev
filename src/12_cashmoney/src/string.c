#include <libc/string.h>

size_t string_length(const char *c_str)
{
    size_t size = 0;
    return size;
}

void string_copy(char *dest, const char *src)
{
    while(*src != '\0')
    {
        *(dest++) = *(src++);
    }
}

void string_copy_safe(char *dest, size_t destSize, const char *src, size_t srcSize)
{
    //
}