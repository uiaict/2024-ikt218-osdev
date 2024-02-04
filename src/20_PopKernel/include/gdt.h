/* Adapted from the James Molloy's GDT implementation totorial at https://archive.is/L3pyA */

#ifndef GDT_H
#define GDT_H

#include "libc/stdint.h"

void initGdt();

// A structure to define an entry in the GDT
struct gdtEntryStruct
{
   uint16_t limitLow; // Lower 16 bits of the limit. Max addressable unit of the segment
   uint16_t baseLow; // Lower 16 bits of the base. The starting address of the segment
   uint8_t baseMiddle; // Next 8 bits of the base. Continuation of the base address
   uint8_t access; // Access flags to determine the rign level. This defines the access rights and the type of segment
   uint8_t granularity; // Granularity of the segment. This defines the size of the segment and the granularity of the limit field
   uint8_t baseHigh; // Last 8 bits of the base.
} __attribute__((packed));
typedef struct gdtEntryStruct gdtEntry_t;


// A structure to define the GDT pointer
struct gdtPtrStruct
{
   uint16_t limit; // Upper 16 bits of all selector limits. Defines the size of the GDT
   uint32_t base;  // Address of the first gdtEntry_t struct
}
 __attribute__((packed));
typedef struct gdtPtrStruct gdtPtr_t;

#endif // GDT_H