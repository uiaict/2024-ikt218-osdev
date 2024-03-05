#include <gdt.h>

// External declaration of the gdt_flush function, implemented in assembly
extern void gdt_flush(addr_t);

// Store GDT entries and pointer
struct gdt_entry_struct gdt_entries[5];
struct gdt_ptr_struct gdt_ptr;

// Function to initialize the GDT
void init_gdt() {
    // Setting the limit of the GDT and then set the base address
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 5) - 1;
    gdt_ptr.base = &gdt_entries;

    // Set up individual GDT entries
    set_gdtGate(0,0,0,0,0); // null segment
    set_gdtGate(1,0,0xFFFFFFFF, 0x9A, 0xCF); // kernel code segment
    set_gdtGate(2,0,0xFFFFFFFF, 0x92, 0xCF); // kernel data segment
    set_gdtGate(3,0,0xFFFFFFFF, 0xFA, 0xCF); // user code segment
    set_gdtGate(4,0,0xFFFFFFFF, 0xF2, 0xCF); // user data segment

    // Load the GDT
    gdt_flush(&gdt_ptr);
}

// Function to set up a GDT entry
void set_gdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {

    // Base address
    gdt_entries[num].base_low = (base & 0xFFFF); // lower 16 bits
    gdt_entries[num].base_middle = (base >> 16) & 0xFF; // middle 8 bits
    gdt_entries[num].base_high = (base >> 24) & 0xFF; // upper 8 bits

    // Limit
    gdt_entries[num].limit = (limit & 0xFFFF); // lower 16 bits

    // Flags and upper 4 bits of limit
    gdt_entries[num].flags = (limit >> 16) & 0x0F;
    gdt_entries[num].flags |= (gran & 0xF0);

    // Access byte
    gdt_entries[num].access = access;
}   
