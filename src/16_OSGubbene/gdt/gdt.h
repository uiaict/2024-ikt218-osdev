#pragma once

// Used teacher notes: https://perara.notion.site/Session-6-Global-Descriptor-Tables-b43f3c4ca20741b7ac46018c0ad6f26e

#define GDT_ENTRIES 5


#include "../include/libc/stdint.h"

// GDT entry structure
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// GDT pointer structure
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Initialize GDT function declaration with extern "C" to allow it being called in c files
#ifdef __cplusplus
extern "C" {
#endif

void gdt_init();

#ifdef __cplusplus
}
#endif
void gdt_load(struct gdt_ptr *gdt_ptr);
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
