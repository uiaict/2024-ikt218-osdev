#include "libc/stdio.h"
#include "libc/stdarg.h"
#include "libc/limits.h"
#include "libc/string.h"
#include "libc/stdlib.h"
#include "io.h"
#include "keyboard.h"

int putchar(int ic) { // ic is the ascii code of the character to be printed

    // Return EOF for invalid ASCII codes
    if (ic < 0 || ic > 255) {
        return EOF;
    } 

    
    char c = (char) ic; // Convert the ASCII code to a character

    switch (c) {
        case '\n':                                      // Newline character
            cursorPos = (cursorPos / 160 + 1) * 160;    // Move to the next line
            break;

        case '\r':                                      // Carriage return character
            cursorPos = cursorPos / 160 * 160;          // Move to the beginning of the line
            break;

        case '\t':                                      // Tab character
            cursorPos = (cursorPos / 8 + 1) * 8;        // Move to the next tab stop
            break;

        case '\b': // Backspace character
        
            // Checks if the cursor is at the beginning of the screen
            if (cursorPos == 0) {
                break;
            }

            cursorPos -= 2; // Move back 2 characters
            break;

        default:                                                        // Regular character
            videoMemory[cursorPos] = c;                                 // Write the character to the video memory
            videoMemory[cursorPos + 1] = currentTextColor;              // Set the text color 
            videoMemory[cursorPos + 1] |= currentBackgroundColor << 4;  // Set the background color
            cursorPos += 2;                                             // Move to the next character. Incremented by 2 because each character is 2 bytes long
    }

    

    // Scroll the screen if the cursor is at the end of the screen
    if (cursorPos >= 160 * 25) { 
        scroll(); 
        cursorPos -= 160; 
    }
    
    setCursorPosition(cursorPos/2); // Set the cursorcursorPosition

    return ic;
}

//  Prints a string of characters
bool print(const char* data, size_t length) {

    // Cast the data to an array of unsigned characters
	const unsigned char* bytes = (const unsigned char*) data; 

    // Print each character
	for (size_t i = 0; i < length; i++) {
        // Return false if putchar returns EOF
        if (putchar(bytes[i]) == EOF) {
            return false;
        }
    }

	return true;
} 


// Printf implementation
int printf(const char* __restrict__ format, ...) {

    // Create a pointer to the first argument
    va_list parameters;
    va_start(parameters, format);

    // Keep track of the number of characters printed
    int written = 0;

    // Loop through each character in the format string
    while (*format != '\0') {

        // If the character is not a format specifier, print it
        if (*format != '%') {
            putchar(*format);
            format++;
            written++;
            continue;
        }

        // Move to the next character
        format++;

        // If the next character is a percentage sign, print it
        if (*format == '%') {
            putchar(*format);
            format++;
            written++;
            continue;
        }

        // Print if char parameter
        if (*format == 'c') {
            char c = (char) va_arg(parameters, int); 
            putchar(c);
            format++;
            written++;
            continue;
        }

        // Print if string parameter
        if (*format == 's') {
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            print(str, len);
            format++;
            written += len;
            continue;
        }

        // Print if signed int parameter
        if (*format == 'd' || *format == 'i') {
            int num = va_arg(parameters, int);
            char str[32];
            itoa(num, str, 10);
            size_t len = strlen(str);
            print(str, len);
            format++;
            written += len;
            continue;
        }

        // Print if unsigned int parameter
        if (*format == 'u') {
            unsigned int num = va_arg(parameters, unsigned int);
            char str[32];
            utoa(num, str, 10);
            size_t len = strlen(str);
            print(str, len);
            format++;
            written += len;
            continue;
        }

        // Print if float parameter
        if (*format == 'f') {
            float num = va_arg(parameters, double);
            char str[32];
            ftoa(num, str, 6);
            size_t len = strlen(str);
            print(str, len);
            format++;
            written += len;
            continue;
        }

        // Print if float with precision parameter
        if (*format == '.') {
            format++;
            int precision = 0;
            while (*format >= '0' && *format <= '9') {
                precision = precision * 10 + (*format - '0');
                format++;
            }
            if (*format == 'f') {
                float num = va_arg(parameters, double);
                char str[32];
                ftoa(num, str, precision);
                size_t len = strlen(str);
                print(str, len);
                format++;
                written += len;
                continue;
            }
        }

        // Print if hex parameter
        if (*format == 'x') {
            unsigned int num = va_arg(parameters, unsigned int);
            char str[32];
            utoa(num, str, 16);
            size_t len = strlen(str);
            print(str, len);
            format++;
            written += len;
            continue;
        }
    }

    // End the list of arguments and return the number of characters printed
    va_end(parameters);
    return written;
}

// Getchar implementation
char getchar() {

    // Wait until there's a character in the buffer
    while (bufferIndex == 0) {}

    // Remove the first character from the buffer
    char c = charBuffer[0];

    for (int i = 0; i < bufferIndex - 1; i++) {
        charBuffer[i] = charBuffer[i + 1];
    }

    bufferIndex--;

    return c;
}

// isspace implementation
int isspace(int c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

// Scanf implementation inspired by https://www.geeksforgeeks.org/how-to-create-your-own-scanf-in-c/
// Only for strings and ints for now. Can be expanded to other types
void scanf(const char* __restrict__ format, ...) {

    va_list args;                                               // Create a pointer to the first argument
    va_start(args, format);                                     // Initialize the pointer

    for (int i = 0; format[i] != '\0'; i++) {                   // Loop through each character in the format string
        if (format[i] == '%') {                                 // If the character is a format specifier, get the input from the user
            i++;
            if (format[i] == 's') {                             // If the format specifier is for a string
                char* var = va_arg(args, char*);                // Get the variable from the argument list
                int j = 0;
                char ch = getchar();                            // Get the first character from the user
                
                while (ch != '\n' && j < 99) {                  // Loop through each character and add it to the variable
                    if (ch == '\b' && j > 0) {                  
                        j--;
                    } else if (!isspace(ch)) {
                        var[j] = ch;
                        j++;
                    }
                    ch = getchar();
                }
                var[j] = '\0';
            } 
            if (format[i] == 'd' || format[i] == 'i') {         // If the format specifier is for an integer
                int* var = va_arg(args, int*);                  // Get the variable from the argument list
                char str[32];
                int j = 0;
                char ch = getchar();                            // Get the first character from the user
                
                while (!isspace(ch) && j < 99) {                // Loop through each character and add it to the variable
                    str[j] = ch;
                    j++;
                    ch = getchar();
                }
                str[j] = '\0';
                *var = atoi(str);
            }
        }
    }

    va_end(args);
}

