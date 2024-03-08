#include "io.h"
#include "macros.h"

// Video memory begins at address 0xb8000
char* videoMemory = (char*) 0xb8000;

// The default text and background color. To change all the characters on the screen, use the changeTextColor and changeBackgroundColor functions. 
// To change the text color going forward, change the currentTextColor variable. To change the background color going forward, change the currentBackgroundColor variable.
uint8_t currentTextColor = DEFAULT_TEXT_COLOR;
uint8_t currentBackgroundColor = DEFAULT_BACKGROUND_COLOR;
int cursorPos = 0; // The position of the cursor on the screen


// Implementation of the outb instruction
void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));      // Send the value to the port
}

// Implementation of the inb instruction
uint8_t inb(uint16_t port) {
    uint8_t result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Enables the cursor 
void enableCursor(uint8_t cursorStart, uint8_t cursorEnd) {
    outb(0x3D4, 0x0A);                                          // Send the command 0x0A to port 0x3D4
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursorStart);             // Send the command 0x0A to port 0x3D5
    outb(0x3D4, 0x0B);                                          // Send the command 0x0B to port 0x3D4
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursorEnd);               // Send the command 0x0B to port 0x3D5
}

// Disables the cursor
void disableCursor() {
    outb(0x3D4, 0x0A);                                          // Send the command 0x0A to port 0x3D4
    outb(0x3D5, 0x20);                                          // Send the command 0x20 to port 0x3D5
}

// Sets the cursor position
void setCursorPosition(uint16_t pos) {
    // Send the high byte
    outb(0x3D4, 14);                                            // 0x3D4 is the port for the cursor
    outb(0x3D5, pos >> 8);                                      // Send the high byte of the position

    // Send the low byte
    outb(0x3D4, 15);                                            // 0x3D4 is the port for the cursor
    outb(0x3D5, pos);                                           // Send the low byte of the position
}

// Scrolls the screen up one line
void scroll() {
    for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1) * 2; i++) { // For each character on the screen
        videoMemory[i] = videoMemory[i + VGA_WIDTH * 2];         // Move the character up one line
    }

    for (int i = 0; i < VGA_WIDTH * 2; i += 2) {                 // For each character on the last line
        videoMemory[(VGA_HEIGHT - 1) * VGA_WIDTH * 2 + i] = ' '; // Set the character to a space
        videoMemory[(VGA_HEIGHT - 1) * VGA_WIDTH * 2 + i + 1] = (currentBackgroundColor << 4) | (videoMemory[i + 1] & 0x0F); // Set the color to the current background color and the existing text color
    }
}


// Clears the screen
void clearScreen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {   // For each character on the screen
        videoMemory[i] = ' ';                                   // Set the character to a space
        videoMemory[i + 1] = currentTextColor;                  // Set the the current text color
        videoMemory[i + 1] |= currentBackgroundColor << 4;      // Set the background color
    }

    cursorPos = 0;                                              // Set the cursor position to the beginning of the screen
    setCursorPosition(cursorPos);                               // Set the cursor position
}

// Changes the text color
void changeTextColor(uint8_t color) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {   // For each character on the screen
        videoMemory[i + 1] = (videoMemory[i + 1] & 0xF0) | (color & 0x0F); // Preserve the background color and set the text color to the specified color
    }

    currentTextColor = color;                                   // Set the current text color to the specified color
}

// Changes the background color 
void changeBackgroundColor(uint8_t color) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT * 2; i += 2) {   // For each character on the screen
        videoMemory[i + 1] = (videoMemory[i + 1] & 0x0F) | (color << 4); // Preserve the text color and set the background color to the specified color
    }
    
    currentBackgroundColor = color;                             // Set the current background color to the specified color
}
