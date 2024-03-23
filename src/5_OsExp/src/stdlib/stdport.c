#include "stdport.h"

void outPortb(uint16_t _port, uint8_t _data) {
    __asm__ __volatile__ ("outb %1, %0" : :  "dN" (_port), "a" (_data));
}