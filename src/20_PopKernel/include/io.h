#ifndef _IO_H
#define _IO_H

#include "libc/stdint.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Default text and background color
#define DEFAULT_TEXT_COLOR 0x07
#define DEFAULT_BACKGROUND_COLOR 0x00

extern uint8_t currentTextColor;
extern uint8_t currentBackgroundColor;
extern int cursorPos;

void initVGA();
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

extern char* videoMemory;

enum vgaColor {
    vgaColorBlack = 0,
    vgaColorBlue = 1,
    vgaColorGreen = 2,
    vgaColorCyan = 3,
    vgaColorRed = 4,
    vgaColorMagenta = 5,
    vgaColorBrown = 6,
    vgaColorLightGrey = 7,
    vgaColorDarkGrey = 8,
    vgaColorLightBlue = 9,
    vgaColorLightGreen = 10,
    vgaColorLightCyan = 11,
    vgaColorLightRed = 12,
    vgaColorLightMagenta = 13,
    vgaColorLightBrown = 14,
    vgaColorWhite = 15,
};

#endif // _IO_H