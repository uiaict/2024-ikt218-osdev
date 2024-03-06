#include "common.h"

void outbyte(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inbyte(uint16_t port)
{
   uint8_t ret = 0;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

uint16_t inword(uint16_t port)
{
   uint16_t ret = 0;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}