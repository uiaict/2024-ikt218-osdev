// Header file for memory functions based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a
#ifndef MEMORY_H
#define MEMORY_H

#include <libc/stdint.h> 
#include <libc/stddef.h> 
#include <isr.h> 

// Struct to represent a memory allocation
typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;


void initKernelMemory(uint32_t* kernelEnd);                             // Initializes the kernel memory

extern void initPaging();                                               // Initializes the paging
extern void pagingMapVirtualToPhys(uint32_t virt, uint32_t phys);       // Maps a virtual address to a physical address

extern char* pmalloc(size_t size);                                      // Allocates a block of page-aligned memory
extern void* malloc(size_t size);                                       // Allocates a block of memory
extern void free(void *memory);                                         // Frees a block of memory


// Declarations for memory manipulation functions
extern void* memcpy(void* dest, const void* src, size_t num );          // Copies num bytes from src to dest 
extern void* memset (void * ptr, int value, size_t num );               // Sets num bytes starting from ptr to value
extern void* memset16 (void *ptr, uint16_t value, size_t num);          // Sets num bytes starting from ptr to a 16-bit value 


void printMemoryLayout();                                               // Prints the memory layout

void pageFaultHandler(registers_t reg);                                 // Handles a page fault

#endif