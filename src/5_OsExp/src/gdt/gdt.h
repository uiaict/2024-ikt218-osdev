#ifndef __GDT_H
#define __GDT_H

#include "stdint.h"

extern void _gdt_flush();

// Entrypoint for GDT
struct gdtEntry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)); // Packed let's the compiler know to not optimize this struct, which could break the GDT

// Special pointer to GDT
struct gdtPtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// GDT Descriptor
void gdtSetGate(int32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// Trying to load gdt in C instead of assembly, might be required due to circumstances I am not aware of-
void gdtLoad(struct gdtPtr *_gdtp);

// Install special pointer and GDT entries, as well as tell CPU where GDT is with _gdt_flush
void gdtInitialize();

#endif