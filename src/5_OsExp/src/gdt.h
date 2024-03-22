#ifndef __GDT_H
#define __GDT_H

#include "stdint.h"

extern void gdt_flush();

// Entrypoint for GDT
struct gdt_entry
{
    uint32_t limit_low;
    uint32_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)); // Packed let's the compiler know to not optimize this struct, which could break the GDT

// Special pointer to GDT
struct gdt_ptr
{
    uint32_t limit;
    uint32_t base;
} __attribute__((packed));


// GDT Descriptor
void gdt_set_gate(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

// Install special pointer and GDT entries, as well as tell CPU where GDT is with gdt_flush
void gdt_install();

#endif