#include "screen.h"

// BUG: Currently the screen size of the Qemu window is not fitted to our dimensions. Look into this.
// VGA MODE 3
#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

uint16_t *textptr; // Beginning of video memory buffer. This is a chunk of memory we can copy and set.
int attribute = 0x0F; // Upper 8-bits defining color, background and foreground. This sets background to black and text to white.
int cursor_x = 0;
int cursor_y = 0;

// Call to initialize screen before trying to use it.
void initScreen(void) {
    textptr = (uint16_t *)VGA_ADDRESS;
    clearScreen();
}

// When the cursor goes below the screen (row 25) this function will act and
// copy all visible text into the buffer and move it up to the top of the screen by
// the amount the cursor is exceeding the "floor".
void scrollScreen(void) {
    unsigned space;
    unsigned temp;

    /* Words (16-bit)
    Space is a 16-bit word, composed of two bytes.
    
    The upper byte denotes background/foreground color, 
    determined by the attribute variable.
    
    The lower byte is denotes what character to write. For example, 0x20 is the space character.

    We perform two bitwise operations here, we OR a bitshifted (8 places) attribute value with the 0x20 value,
    this places the color value and character values in the correct place for the 16-bit memory address.
    */
    space = 0x20 | (attribute << 8); // 0x20 is the space character. A blank screen is actually made up of space characters.
    if (cursor_y >= VGA_ROWS) {
        temp = cursor_y - VGA_ROWS + 1; // How many rows we need to scroll up. Line 1 is the beginning of the screen, not 0.
        
        memCopy(textptr, textptr + temp * VGA_COLS, (VGA_ROWS - temp) * VGA_COLS * 2); // Copy content in memory buffer starting from line 1.
        
        memSet(textptr + (VGA_ROWS - temp) * VGA_COLS, space, VGA_COLS); // Write spaces to the new row(s). "w" signifies word, meaning 16-bit.
        
        cursor_y = VGA_ROWS - 1; // Set cursor to the last line.
    }
}

// Function to display the cursor blinker's position in the terminal.
void cursorBlinker(void) {
    unsigned temp;

    // Cursor location in the array
    temp = cursor_y * VGA_COLS + cursor_x;

    // Instructions to CRT (VGA controller)
    outPortb(0x3D4, 14);            // Select high register
    outPortb(0x3D5, temp >> 8);     // Write position of cursor to high register
    outPortb(0x3D4, 15);            // Select low register
    outPortb(0x3D5, temp);          // Write position of cursor to low register
}

void clearScreen() {
    unsigned space;

    space = 0x20 | (attribute << 8);

    // Write spaces into the memory buffer to populate the entire screen with spaces.
    for (int i = 0; i < 25; i++) {
        memSet(textptr + i * VGA_COLS, space, VGA_COLS);
    }

    // Set position of the cursor on the cleared screen.
    cursor_x = 0;
    cursor_y = 0;
    cursorBlinker();
}

void putChar(uint8_t c) {
    uint16_t *where; // Location on the screen to put the character
    unsigned attr = attribute << 8; // Color of the character

    if (c == 0x08 && cursor_x != 0) { cursor_x--; }             // Backspace (0x08), move cursor back one space
    if (c == 0x09) { cursor_x = (cursor_x + 8) & ~(8 - 1); }    // Tab (0x09), but only if divisible by 8.
    if (c == '\r') { cursor_x = 0; }                            // Home key, return to leftmost margin.    
    if (c == '\n') { cursor_x = 0; cursor_y++; }                // Enter key, return to leftmost margin.

    // Printable characters from 'space' (1st printable char) and onward.
    if (c >= ' ') {
        where = textptr + (cursor_y * 80 + cursor_x);
        *where = c | attr;
        cursor_x++;
    }

    if (cursor_x >= VGA_COLS) { cursor_x = 0; cursor_y++; } // Newline when we hit the last column (rightmost).

    scrollScreen(); // Scroll screen if needed.
    cursorBlinker(); // Keep track of the cursor in the console.
}

void putString(uint8_t *string) {
    for (int i = 0; i < stringLen(string); i++) {
        putChar(string[i]); // Loop over provided buffer and print characters.
    }
}

// Define text color. Default is preset to black background and white foreground (text).
// Options are numbered 0 to 15, outlined here:
// http://www.osdever.net/bkerndev/Docs/printing.htm
void setTextColor(uint8_t background_color, uint8_t foreground_color) {
    attribute = (background_color << 4) | (foreground_color & 0x0F);
}