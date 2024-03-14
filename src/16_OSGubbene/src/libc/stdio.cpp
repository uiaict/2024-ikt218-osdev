#include "../../include/libc/stdio.h"


// Define memory-mapped I/O address for VGA text mode buffer
volatile unsigned short* VGA_BUFFER = (volatile unsigned short*)0xB8000;

// VGA color codes
enum vga_colors {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GRAY = 7,
    VGA_COLOR_DARK_GRAY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

// Creates a vga entry which is used to print a character to the terminal 
// using vga text mode buffer with set color and background color
unsigned short vga_entry(unsigned char u_char, unsigned char char_color, unsigned char bgcolor) {
    return (unsigned short) u_char | (unsigned short) char_color << 8 | (unsigned short) bgcolor << 12;
}

int putchar(int int_char) {
    static size_t vga_column = 0;
    static size_t vga_row = 0;

    unsigned short entry = vga_entry(int_char, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    
    if (int_char == '\n') {
        vga_column = 0;
        vga_row++;
    } else {
        VGA_BUFFER[vga_row * 80 + vga_column] = entry;
        vga_column++;
        if (vga_column == 80) {
            vga_column = 0;
            vga_row++;
        }
    }
    
    return int_char;
}


int printf(const char* __restrict__ format_string, ...) {
    va_list args;
    va_start(args, format_string);
    
    int printed = 0;
    // Loop through format string
    for (const char* char_ptr = format_string; *char_ptr != '\0'; char_ptr++) {
        // If current character is not a format specifier, just print it
        if (*char_ptr != '%') {
            if (putchar(*char_ptr) == EOF) {
                return EOF;
            } else {
                printed++;
            }
            continue;
        }
        
        // Handle format specifiers: Currently supports %s and %c for strings and characters (More coming soon)
        switch (*(++char_ptr)) {
            case 's': {
                const char* string_argument = va_arg(args, const char*);
                size_t len = strlen(string_argument);
                for (size_t i = 0; i < len; i++) {
                    if (putchar(string_argument[i]) == EOF) {
                        return EOF;
                    }
                    printed++;
                }
                break;
            }
            case 'c': {
                int int_char = va_arg(args, int);
                if (putchar(int_char) == EOF) {
                    return EOF;
                } else {
                    printed++;
                }
                break;
            }
            default:
                // If format string includes an unsupported format specifier, print the '%'
                if (putchar('%') == EOF) {
                    return EOF;
                } else {
                    printed++;
                }
                putchar(*char_ptr);
                break;
        }
    }
    
    // Clear arguments list from memory
    va_end(args);
    return printed;
}