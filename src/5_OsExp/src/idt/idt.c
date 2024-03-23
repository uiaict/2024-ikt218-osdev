#include "idt.h"

#include "stdmem.h"

/*
Allocating 256 entries to the IDT. We are only using 32 entries, however,
the remaining entries will be set to avoid any unhandled exceptions if
we hit a cleared presence bit (bit 7 in IDT).
*/
struct idtEntry idt[256];

struct idtPtr _idtp;

void idtSetGate(int32_t index, uint32_t base, uint16_t sel, uint8_t flags) {
     /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
   idt[index].base_low = base & 0xFFFF;                     // Lower 16 bits
   idt[index].base_high = (base >> 16) & 0xFFFF;            // Upper 16 bits
   idt[index].sel = sel;                                    // Kernel segment
   idt[index].always0 = 0;
   idt[index].flags = flags;
}

void idtInitialize() {
    _idtp.limit = (sizeof (struct idtEntry) * 256) - 1;     // Setting the limit, count starts from 0, hence -1.
    _idtp.base = (uint32_t) &idt;                                       // Taking reference of idt

    // CLearing every entry in idt
    memSet(&idt, 0, sizeof(struct idtEntry) * 256);

    idt_load();
}