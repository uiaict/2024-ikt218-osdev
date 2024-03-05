#include <../include/function.h>
#include <../include/libc/stdint.h>

// Define constants for VGA width and height
#define width 80
#define height 25

// Define a pointer to the VGA text buffer starting address
uint16_t *const vga = (uint16_t *const)0xB8000;

// Keep track of the current column and row in the VGA buffer
int col, row = 0;

// Custom function for writing to the VGA text buffer
void terminal_write(const char *string) {
    // Initialize a pointer to the input string
    char *ptr = string;

    do {
        // Write the character to the VGA buffer with a default attribute (white on black)
        vga[row * width + col] = *ptr | 0x0700;
        col++;
        *ptr++;
    } while(*ptr != 0x00);

    return;
}