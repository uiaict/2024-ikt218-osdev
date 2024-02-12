#include <libc/string.h>
#include "libc/stdint.h"
#include "libc/stddef.h"

// Implementation of strlen
size_t strlen(char *str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

// Implementation of strchr
char *strchr(char *str, int c) {

	// Loop through the string until the null terminator
    while (*str != '\0') {
		// Return the pointer if the character is found
        if (*str == c) 
            return str;
        str++;
    }

	// Return null if the character is not found
    if (c == '\0')
        return str;
    return NULL;
}

// Implementation of strrev function adapted from https://www.geeksforgeeks.org/implement-itoa/
void strrev(char str[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }
}

// Implementation of memset
void *memset(void *str, int c, size_t n) {
    unsigned char* ptr = (unsigned char*) str;
    for (size_t i = 0; i < n; i++)
        ptr[i] = c;
    return str;
}