#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "isr.h"
#include "io.h"
#include "libc/stdbool.h"

#define KEYBOARD_DATA_PORT 0x60

// Define the scancode for the shift and caps lock keys. Since special keys are handled by holding in shift 
#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define CAPS_LOCK 0x3A
#define ESCAPE 0x01

void initKeyboard();
void keyboardHandler(registers_t reg);
void freeWrite(char ascii);
void draw(uint8_t scanCode);

// Keeps track of shift key and caps lock
static bool shiftPressed = false; 
static bool capsLockEnabled = false;
static bool drawingMode = false;
extern uint8_t drawingColor;


// There are two scenarios where we want to write to the screen
// 1. The user types freely and whatever they type is written to the screen
// 2. The user is typing a command or we want to capture what the user has typed. In either case, enter is pressed to signal the end of the input
/* extern bool captureInput; */

// Deafult lookup table for US QWERTY keyboard
static const char defaultLookup[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', // 0x00 to 0x0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', // 0x10 to 0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 0x20 to 0x2F
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, // 0x30 to 0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 0x40 to 0x4F
    '2', '3', '0', '.' // 0x50 to 0x53
};

// Lookup table for when the shift key is pressed
static const char shiftLookup[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', // 0x00 to 0x0F
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S', // 0x10 to 0x1F
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~', 0, '|', 'Z', 'X', 'C', 'V', // 0x20 to 0x2F
    'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, // 0x30 to 0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 0x40 to 0x4F
    '2', '3', '0', '.' // 0x50 to 0x53
};

// Lookup table for when the caps lock key is pressed
static const char capsLockLookup[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', // 0x00 to 0x0F
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n', 0, 'A', 'S', // 0x10 to 0x1F
    'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', 0, '\\', 'Z', 'X', 'C', 'V', // 0x20 to 0x2F
    'B', 'N', 'M', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, // 0x30 to 0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 0x40 to 0x4F
    '2', '3', '0', '.' // 0x50 to 0x53
};

// Lookup table for when the shift and caps lock keys are pressed
static const char shiftCapsLockLookup[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', // 0x00 to 0x0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n', 0, 'a', 's', // 0x10 to 0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '"', '~', 0, '|', 'z', 'x', 'c', 'v', // 0x20 to 0x2F
    'b', 'n', 'm', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, // 0x30 to 0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1', // 0x40 to 0x4F
    '2', '3', '0', '.' // 0x50 to 0x53
};





#endif

