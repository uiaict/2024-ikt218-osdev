// Used teacher notes: https://perara.notion.site/Session-6-Global-Descriptor-Tables-b43f3c4ca20741b7ac46018c0ad6f26e

#include "gdt.h"
#include "../include/libc/stdio.h"

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gdt_ptr;

extern "C" void gdt_flush(uint32_t);
extern "C"
{
    void gdt_init()
    {
        printf("Initializing GDT\n");

        // Set the GDT limit
        gdt_ptr.limit = sizeof(struct gdt_entry) * GDT_ENTRIES - 1;
        gdt_ptr.base = (uint32_t)&gdt;

        // num, base, limit, access, granularity
        gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
        gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

        printf("Segment gates set\n");

        // Load the GDT
        gdt_load(&gdt_ptr);
        printf("GDT loaded\n");

        // Flush GDT pointer (Reload segmet registers)
        gdt_flush((uint32_t)&gdt_ptr);
    }
}

void gdt_load(struct gdt_ptr *gdt_ptr)
{
    asm volatile("lgdt %0" : : "m"(*gdt_ptr));
}

void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;

    printf("A GDT gate was set\n");
}