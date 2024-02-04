/* Adapted from the James Molloy's GDT implementation totorial at https://archive.is/L3pyA */

#include "gdt.h"
#include "libc/stdint.h"

extern void gdtFlush(uint32_t gdtPtr);

static void gdtSetGate(int32_t,uint32_t,uint32_t,uint8_t,uint8_t);

gdtEntry_t gdtEntries[5];
gdtPtr_t gdtPtr;

// Initializes the GDT
void initGdt()
{
   // Sets the size and base of the GDT pointer
   gdtPtr.limit = (sizeof(gdtEntry_t) * 5) - 1;
   gdtPtr.base  = (uint32_t)&gdtEntries;

   // Sets the default entries of the GDT
   gdtSetGate(0, 0, 0, 0, 0); // Null segment
   gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
   gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
   gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
   gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

   gdtFlush((uint32_t)&gdtPtr); // Flushes the old GDT and installs the new one
}

// Set the value of one GDT entry.
static void gdtSetGate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdtEntries[num].baseLow = (base & 0xFFFF); // Lower 16 bits of the base
   gdtEntries[num].baseMiddle = (base >> 16) & 0xFF; // Middle 8 bits of the base
   gdtEntries[num].baseHigh = (base >> 24) & 0xFF; // Upper 8 bits of the base
   gdtEntries[num].limitLow = (limit & 0xFFFF); // Lower 16 bits of the limit
   gdtEntries[num].granularity = (limit >> 16) & 0x0F; // Upper 4 bits of the limit
   gdtEntries[num].granularity |= gran & 0xF0; // Add the granularity to the limit
   gdtEntries[num].access = access; // Access flags
}