#pragma once

#include <libc/stdint.h>

#define array_size(array) ((sizeof(array)) / (sizeof(array[0])))

// Write a byte to the specified port
static inline void outbyte(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

// Read a byte from the specified port
static inline uint8_t inbyte(uint16_t port)
{
   uint8_t ret = 0;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// Read a word from the specified port
static inline uint16_t inword(uint16_t port)
{
   uint16_t ret = 0;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// Absolute value
static inline int32_t abs32(int32_t value)
{
    return (value < 0 ? -value : value);
}
// Absolute value
static inline int16_t abs16(int16_t value)
{
    return (value < 0 ? -value : value);
}
// Absolute value
static inline int8_t abs8(int8_t value)
{
    return (value < 0 ? -value : value);
}
