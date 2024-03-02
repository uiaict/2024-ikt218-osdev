#ifndef IO_H
#define IO_H

#include "libc/stdint.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Default text and background color
#define DEFAULT_TEXT_COLOR 0x07
#define DEFAULT_BACKGROUND_COLOR 0x00

// Variables to store the current text/background color, cursor position and video memory
extern uint8_t currentTextColor;
extern uint8_t currentBackgroundColor;
extern int cursorPos;
extern char* videoMemory;

// Function declarations
void enableCursor(uint8_t cursorStart, uint8_t cursorEnd);
void disableCursor();
void setCursorPosition(uint16_t position);
void clearScreen();
void changeTextColor(uint8_t color);
void changeBackgroundColor(uint8_t color);
uint16_t getCursorPosition();
void outb(unsigned short port, unsigned char val);
uint8_t inb(uint16_t port);
void scroll();

// VGA color codes
enum vgaColor {
    vgaColorBlack = 0,          // Black
    vgaColorBlue = 1,           // Blue
    vgaColorGreen = 2,          // Green
    vgaColorCyan = 3,           // Cyan
    vgaColorRed = 4,            // Red
    vgaColorMagenta = 5,        // Magenta
    vgaColorBrown = 6,          // Brown
    vgaColorLightGrey = 7,      // Light Grey
    vgaColorDarkGrey = 8,       // Dark Grey
    vgaColorLightBlue = 9,      // Light Blue
    vgaColorLightGreen = 10,    // Light Green
    vgaColorLightCyan = 11,     // Light Cyan
    vgaColorLightRed = 12,      // Light Red
    vgaColorLightMagenta = 13,  // Light Magenta
    vgaColorLightBrown = 14,    // Light Brown
    vgaColorWhite = 15,         // White
};

#endif // _IO_H