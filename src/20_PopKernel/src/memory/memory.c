// Source file for memory.c based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a
#include "memory.h"
#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/limits.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <isr.h>
#include <kernelUtils.h>


static uint32_t* pageDir = 0;                               // Define a pointer to the page directory and initialize it to zero
static uint32_t pageDirLoc = 0;                             // Define the location of the page directory and initialize it to zero
static uint32_t* lastPage = 0;                              // Define a pointer to the last page and initialize it to zero

// Function top map a virtual to a physical address
void pagingMapVirtualToPhys(uint32_t virt, uint32_t phys) {
    uint16_t id = virt >> 22;                               // Gets the upper 10bits of the virtual address. This is the index of the page directory entry

    for (int i = 0; i < 1024; i++){                         // Loop through the page table entries
        lastPage[i] = phys | 3;                             // Set the page table entry to the physical address and set the flags to 3
        phys += 4096;                                       // Increment the physical address by 4096 (4KB)
    } 

    pageDir[id] = ((uint32_t)lastPage) | 3;                 // Set the page directory entry to the last page and set the flags to 3
    lastPage = (uint32_t*)(((uint32_t)lastPage) + 4096);    // Increment the last page by 4096 (4KB)
}

// Function to enable paging
void enablePaging() {
    asm volatile("mov %%eax, %%cr3": :"a"(pageDirLoc));     // Load the physical address of the page directory into the CR3 register
    asm volatile("mov %cr0, %eax");                         // Load the CR0 register into the EAX register
    asm volatile("orl $0x80000000, %eax");                  // Set the paging enable bit in the EAX register
    asm volatile("mov %eax, %cr0");                         // Load the EAX register into the CR0 register to enable paging
}


// Function to initialize the paging
void initPaging() {
    printf("Initializing paging\n");                        // Print a message to the screen. Remove later to not clutter the screen
    registerInterruptHandler(14, &pageFaultHandler);        // Register the page fault handler
    pageDir = (uint32_t*)0x400000;                          // Set the page directory to start at 4MB
    pageDirLoc = (uint32_t)pageDir;                         // Set the page directories physical address to the page directory location
    lastPage = (uint32_t*)0x401000;                         // Set the last page to start at 4MB + 4KB

    for (int i = 0; i < 1024; i++){                         // Loop through the page directory entries
        pageDir[i] = 0 | 2;                                 // Set the page directory entry to 0 and set the flags to 2
    }      
        
    pagingMapVirtualToPhys(0, 0);                           // Map the first 4MB of virtual memory to the first 4MB of physical memory
    pagingMapVirtualToPhys(0x400000, 0x400000);             // Map the second 4MB of virtual memory to the second 4MB of physical memory
    enablePaging();                                         // Enable paging
    printf("Paging initialized\n");                         // Print a message to the screen. Remove later to not clutter the screen
}

// Page fault handler based on James Molloy's implementation found at https://archive.is/8MXkb#selection-3583.1-3621.4
void pageFaultHandler(registers_t regs)
{
   
   uint32_t faultAddress;
   asm volatile("mov %%cr2, %0" : "=r" (faultAddress));     // Get the faulting address

   int present  = !(regs.errCode & 0x1);                    // Page not present
   int rw = regs.errCode & 0x2;                             // Write operation?
   int us = regs.errCode & 0x4;                             // Processor was in user-mode?
   int reserved = regs.errCode & 0x8;                       // Overwritten CPU-reserved bits of page entry?
   int id = regs.errCode & 0x10;                            // Caused by an instruction fetch?

   // Output an error message.
   printf("Page fault! ( ");                                // Print a message to the screen
   if (present) {printf("present ");}                       // If the page is not present, print "present"
   if (rw) {printf("read-only ");}                          // If the operation is a write operation, print "read-only"
   if (us) {printf("user-mode ");}                          // If the processor was in user-mode, print "user-mode"
   if (reserved) {printf("reserved ");}                     // If the page entry has overwritten CPU-reserved bits, print "reserved"
   printf(") at 0x");
   printf("%x", faultAddress);                              // Print the faulting address
   printf("\n");
   panic("Page fault");                                     // Panic
}