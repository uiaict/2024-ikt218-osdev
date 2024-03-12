/* Adapted from the James Molloy's GDT/IDT implementation totorial at https://archive.is/L3pyA */
#ifndef DESTABLES_H
#define DESTABLES_H

#include <libc/stdint.h>

void initGdt();
void initIdt();
void initDesTables();

// A structure to define an entry in the GDT
struct gdtEntryStruct {
    uint16_t limitLow;      // Lower 16 bits of the limit. Max addressable unit of the segment
    uint16_t baseLow;       // Lower 16 bits of the base. The starting address of the segment
    uint8_t baseMiddle;     // Next 8 bits of the base. Continuation of the base address
    uint8_t access;         // Access flags to determine the rign level. This defines the access rights and the type of segment
    uint8_t granularity;    // Granularity of the segment. This defines the size of the segment and the granularity of the limit field
    uint8_t baseHigh;       // Last 8 bits of the base.
} __attribute__((packed));
typedef struct gdtEntryStruct gdtEntry_t;


// A structure to define the GDT pointer
struct gdtPtrStruct {
    uint16_t limit;         // Upper 16 bits of all selector limits. Defines the size of the GDT
	uint32_t base;          // Address of the first gdtEntry_t struct
}
 __attribute__((packed));
typedef struct gdtPtrStruct gdtPtr_t;

// Defines an IDT entry
struct idtEntryStruct {
   uint16_t baseLow;        // Lower 16 bits of jump address            
   uint16_t sel;            // Kernel segment selector          
   uint8_t  always0;   
   uint8_t  flags;               
   uint16_t baseHigh;       // Upper 16 bits of jump address           
} __attribute__((packed));
typedef struct idtEntryStruct idtEntry_t;

// A struct describing a pointer to the IDT
struct idtPtrStruct {
   uint16_t limit;
   uint32_t base;              
} __attribute__((packed));
typedef struct idtPtrStruct idtPtr_t;

// ISRs reserved for CPU exceptions
extern void isr0 ();    // Division by zero
extern void isr1 ();    // Debug
extern void isr2 ();    // Non-maskable interrupt
extern void isr3 ();    // Breakpoint exception
extern void isr4 ();    // 'Into detected overflow'
extern void isr5 ();    // Out of bounds exception
extern void isr6 ();    // Invalid opcode
extern void isr7 ();    // No coprocessor
extern void isr8 ();    // Double fault
extern void isr9 ();    // Coprocessor segment overrun
extern void isr10 ();   // Bad TSS
extern void isr11 ();   // Segment not present
extern void isr12 ();   // Stack fault
extern void isr13 ();   // General protection fault
extern void isr14 ();   // Page fault
extern void isr15 ();   // Unknown interrupt exception
extern void isr16 ();   // Coprocessor fault
extern void isr17 ();   // Alignment check exception
extern void isr18 ();   // Machine check exception
extern void isr19 ();   // 19-31 reserved
extern void isr20 ();  
extern void isr21 (); 
extern void isr22 (); 
extern void isr23 (); 
extern void isr24 (); 
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 ();

// IRQs
extern void irq0 ();    // IRQ0
extern void irq1 ();    // IRQ1
extern void irq2 ();    // IRQ2
extern void irq3 ();    // IRQ3
extern void irq4 ();    // IRQ4
extern void irq5 ();    // IRQ5
extern void irq6 ();    // IRQ6
extern void irq7 ();    // IRQ7
extern void irq8 ();    // IRQ8
extern void irq9 ();    // IRQ9
extern void irq10 ();   // IRQ10
extern void irq11 ();   // IRQ11   
extern void irq12 ();   // IRQ12
extern void irq13 ();   // IRQ13
extern void irq14 ();   // IRQ14
extern void irq15 ();   // IRQ15


#endif // DESTABLES_H