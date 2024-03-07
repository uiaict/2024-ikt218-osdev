#include "descriptor_tables.h"

// Lets us access our ASM functions from our C code.
extern void gdt_flush(uint32_t);

#define GDT_ENTRY_COUNT 5
#define GDT_LIMIT 0xFFFFFFFF
#define IDT_ENTRY_COUNT 256

gdt_entry_t gdt_entries[GDT_ENTRY_COUNT];
gdt_ptr_t   gdt_ptr;
//idt_entry_t idt_entries[256];
//idt_ptr_t   idt_ptr;

static void gdt_set(int32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Shifts and truncates the 32 bit base value to fit into the 3 partitions
    gdt_entries[index].base_low    = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high   = (base >> 24) & 0xFF;

    // Truncates limit
    gdt_entries[index].limit_low   = (limit & 0xFFFF);

    // Sets half of granularity from the upper part of limit
    gdt_entries[index].granularity = (limit >> 16) & 0x0F;

    // Sets the upper half of granularity from gran
    gdt_entries[index].granularity |= gran & 0xF0;
    gdt_entries[index].access      = access;
}

static void init_gdt()
{
    gdt_ptr.limit = sizeof(gdt_entries) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    gdt_set(0, 0, 0, 0, 0);               // Null descriptor segment
    gdt_set(1, 0, GDT_LIMIT, 0x9A, 0xCF); // Kernel code segment
    gdt_set(2, 0, GDT_LIMIT, 0x92, 0xCF); // Kernel data segment
    gdt_set(3, 0, GDT_LIMIT, 0xFA, 0xCF); // User mode code segment
    gdt_set(4, 0, GDT_LIMIT, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdt_ptr);
}

void init_descriptor_tables()
{
    // Initialise the global descriptor table.
    init_gdt();
}