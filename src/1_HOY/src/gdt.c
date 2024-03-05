//code is based on examples from the course materials - especially session 6 and copilot. 

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/multiboot2.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/gdt.h"

extern void gdt_flush(uint32_t);



//define the GDT and the GDT pointer
#define GDT_ENTRIES 3

gdt_entry_t gdt[GDT_ENTRIES];
gdt_ptr_t gdt_ptr; 

void init_gdt() {
    //set the limit and base of the GDT pointer
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    //set the default entries of the GDT
    set_gdt_entry(0, 0, 0, 0, 0);                // Null segment
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

    //load the GDT
    gdt_load(&gdt_ptr);

    //flush the GDT pointer
    gdt_flush((uint32_t)&gdt_ptr);
}
//load the GDT
void gdt_load(struct gdt_ptr *gdt_ptr) {
    asm volatile("lgdt (%0)" : : "r" (gdt_ptr));
}

//set the GDT entry
void set_gdt_entry(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity){
    
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= granularity & 0xF0;
    gdt[num].access = access;
}