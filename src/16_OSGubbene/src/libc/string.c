#include "../../include/libc/string.h"


// Function calculates the length of a null-terminated string by checking for the null-terminator
size_t strlen(const char* str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}