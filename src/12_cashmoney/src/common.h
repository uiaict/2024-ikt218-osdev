#pragma once

#include <libc/stdint.h>

// Write a byte to the specified port
void outbyte(uint16_t port, uint8_t value);
// Read a byte from the specified port
uint8_t inbyte(uint16_t port);
// Read a word from the specified port
uint16_t inword(uint16_t port);