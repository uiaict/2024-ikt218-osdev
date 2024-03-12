// Source file for memutils.c based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a
#include "memory.h"
#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/limits.h>
#include <libc/stdio.h>
#include <libc/string.h>

// Function to copy memory from source to destination
void* memcpy(void* dest, const void* src, size_t count ) {
    char* dst8 = (char*)dest;                           // Cast the destination pointer to char*
    char* src8 = (char*)src;                            // Cast the source pointer to char*

    if (count & 1) {                                    // If the count is odd
        dst8[0] = src8[0];                              // Copy one byte from source to destination
        dst8 += 1;                                      // Increment destination pointer by one byte
        src8 += 1;                                      // Increment source pointer by one byte
    }

    count /= 2;                                         // Divide the count by two to copy 2 bytes at a time
    while (count--) {                                   // Loop through each pair of 2 bytes
        dst8[0] = src8[0];                              // Copy the first byte of the pair from source to destination
        dst8[1] = src8[1];                              // Copy the second byte of the pair from source to destination

        dst8 += 2;                                      // Increment destination pointer by 2 bytes
        src8 += 2;                                      // Increment source pointer by 2 bytes
    }

    return (void*)dest;                                 // Return the destination pointer
}

// Function to set a block of memory with a 16-bit value
void* memset16 (void *ptr, uint16_t value, size_t num) {
    uint16_t* p = ptr;                                  // Cast the pointer to uint16_t*
    while(num--)
        *p++ = value;                                   // Set each 2-byte element to the given value
    return ptr;                                         // Return the pointer to the block of memory
}

// Function to set a block of memory with a byte value
void* memset (void * ptr, int value, size_t num ) {
    unsigned char* p=ptr;                               // Cast the pointer to unsigned char*
    while(num--)
        *p++ = (unsigned char)value;                    // Set each byte to the given value
    return ptr;                                         // Return the pointer to the block of memory
}
