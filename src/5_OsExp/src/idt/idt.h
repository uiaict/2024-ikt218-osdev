#ifndef __IDT_H
#define __IDT_H

#include "stdint.h"

extern void idt_load();

struct idtEntry {
    uint16_t base_low;
    uint16_t base_high;
    uint16_t sel; // Kernel segment
    uint8_t always0; // Always 0

    /*
    Bit 7: Present or not
    Bit 6-5: Descriptor Privilege Level, 0-3
    Bit 4-0: Always 0b---0 1110 = 14
    */
    uint8_t flags;
} __attribute__((packed));

struct idtPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idtSetGate(int32_t index, uint32_t base, uint16_t sel, uint8_t flags);

void idtInitialize();

#endif