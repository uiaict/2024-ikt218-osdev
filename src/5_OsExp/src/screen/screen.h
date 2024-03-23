#ifndef __SCREEN_H
#define __SCREEN_H

#include "stdint.h"
#include "stdmem.h"
#include "stdport.h"
#include "stdtxt.h"

void initScreen(void);

void clearScreen(void);

void scrollScreen(void);

void cursorBlinker(void);

void putChar(uint8_t c);

void putString(uint8_t *string);

void setTextColor(uint8_t background_color, uint8_t foreground_color);

#endif