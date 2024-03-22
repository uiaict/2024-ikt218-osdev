#include "gdt.h"

struct gdt_entry gdt[3];

struct gdt_ptr gdtp;

void gdt_set_gate(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    // Base addresses in the descriptor, length 32 bits
    gdt[index].base_low = (base & 0xFFFF);                  // Lower 16 bits, AND'ing bitmask to preserve 16 bits.
    gdt[index].base_middle = (base >> 16) & 0x00FF;         // Middle 8 bits, AND'ing bitmask to preserve 8 bits, shifted right 16 spaces
    gdt[index].base_high = (base >> 24) & 0x00FF;           // High 8 bits, AND'ing bitmask to preserve 8 bits, shifted right 24 spaces
    
    // Limits of the descriptor
    gdt[index].limit_low = (limit & 0xFFFF);                // Lower limit 16 bits
    gdt[index].granularity = ((limit >> 16) & 0x000F);      // High 4 bits of the limit, shifted right 16 spaces
    
    // Granularity and access flags in the descriptor
    gdt[index].granularity |= (gran & 0xF0);                // Granularity 4 bits (upper nibble), OR'ed with gran
    gdt[index].access = access;                             // Access flags 8 bits
}

void gdt_install()
{
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1; // Limit of GDT, ie. the size in memory of the GDT
    gdtp.base = (uint32_t)&gdt; // Pointer to start of GDT in memory
    
    gdt_set_gate(0, 0, 0, 0, 0); // NULL descriptor, index 0

    // The index (descriptor) is 1, denoting code segment
    // Base address: 0
    // Limit (0xFFFFFFFF): 4GB
    /* Access (init: 10011010) */ 
        // bit 7: present. Set bit means it's in memory. Used for virtual memory.
        // bit 6-5: privilege. Kernel is 00, user is 11.
        // bit 4: descriptor type. Set bit means code, cleared bit means data.
        // bit 3: Executable. Set bit means code, cleared bit means data.
        // bit 2: Conforming (memory protection). Cleared bit means this segment cannot be accessed by lower privilege level segments.
        // bit 1: Readable/Writable. Set bit means code segment is readable, data segment is writable.
        // bit 0: Accessed. Set bit means CPU has accessed this segment.
        // Settings:
        // 7: present | 6-5: priviledge kernel access | 4: type is code | 3: executable | 2: protected memory | 1: Readable | 0: Not accessed by CPU 
    /* Granularity (init: 11001111) */
        // bit 7: granularity. Set bit means limit is in 4kb blocks, cleared bit means limit is in bytes.
        // bit 6: Size. Set bit means 32 bit protected mode, cleared bit means 16 bit protected mode.
        // bit 5: Reserved. Set bit means reserved, cleared bit means 8086 mode.
        // bit 4: Available for system use.
        // bit 3-0: Limit 16-19.
        // Settings:
        // 7: 4KB | 6: 32 bit protected mode | 5: 8086 mode | 4: Not available for system use
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0b10011010, 0b11001111);

    // Index 2 denoting data segment
    // Otherwise the same as code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0b10010010, 0b11001111); 

    // Flush old GDT and install new changes
    gdt_flush();
}
