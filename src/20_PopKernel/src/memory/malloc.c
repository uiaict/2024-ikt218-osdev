// Source file for malloc.c based on Per-Arne Andersen's implementation found at https://perara.notion.site/IKT218-Advanced-Operating-Systems-2024-bfa639380abd46389b5d69dcffda597a
#include "memory.h"
#include <libc/stddef.h>
#include <libc/stdint.h>
#include <libc/limits.h>
#include <libc/stdio.h>
#include <libc/string.h>
#include <kernelUtils.h>

#define MAX_PAGE_ALIGNED_ALLOCS 32                              // Define the maximum number of page-aligned allocations

uint32_t lastAlloc = 0;                                         // Variable to keep track of the last allocation
uint32_t heapBegin = 0;                                         // Variable to keep track of the beginning of the heap
uint32_t heapEnd = 0;                                           // Variable to keep track of the end of the heap
uint32_t pheapBegin = 0;                                        // Variable to keep track of the beginning of the physical heap
uint32_t pheapEnd = 0;                                          // Variable to keep track of the end of the physical heap
uint8_t *pheapDesc = 0;                                         // Variable to keep track of the physical heap descriptor
uint32_t memoryUsed = 0;                                        // Variable to keep track of the memory used

// Initializes the kernel memory
void initKernelMemory(uint32_t *kernelEnd) {

    lastAlloc = (uint32_t)kernelEnd + 0x1000;                   // Set the last allocation to the kernel end
    heapBegin = lastAlloc;                                      // Set the heap begin to the last allocation
    pheapEnd = 0x400000;                                        // Set the heap end 
    pheapBegin = pheapEnd -(MAX_PAGE_ALIGNED_ALLOCS * 4096);    // Set the physical heap begin
    heapEnd = pheapBegin;                                       // Set the heap end to the physical heap begin
    memset((char *)heapBegin, 0, heapEnd - heapBegin);          // Set the memory to 0
    pheapDesc = (uint8_t *)malloc(MAX_PAGE_ALIGNED_ALLOCS);     // Allocate the maximum number of page-aligned allocations
    printf("Kernel heap starts at 0x%x\n", lastAlloc);          // Print the kernel heap start

}

// Function to print the memory layout
void printMemoryLayout() {
    printf("Memory used: %d bytes\n", memoryUsed);                      
    printf("Memory free: %d bytes\n", heapEnd - heapBegin - memoryUsed);
    printf("Heap size: %d bytes\n", heapEnd - heapBegin);
    printf("Heap start: 0x%x\n", heapBegin);
    printf("Heap end: 0x%x\n", heapEnd);
    printf("PHeap start: 0x%x\nPHeap end: 0x%x\n", pheapBegin, pheapEnd);
}


// Function to free a block of memory
void free(void *memory) {
    alloc_t *alloc = (memory - sizeof(alloc_t));                // Set the allocation to the memory - the size of the allocation
    memoryUsed -= alloc->size + sizeof(alloc_t);                // Decrement the memory used by the size of the allocation + the size of the allocation struct

    alloc->status = 0;                                          // Set the status of the allocation to 0
}

// Function to free a block of page-aligned memory
void pfree(void *memory) {
    if (memory < pheapBegin || memory > pheapEnd){
        return;                                                 // If the memory is outside the heap, return
    }
    
    // Determine the page ID
    uint32_t ad = (uint32_t)memory;                             // Set the address to the memory
    ad -= pheapBegin;                                           // Subtract the physical heap begin from the address
    ad /= 4096;                                                 // Divide the address by 4096 to get the page ID

    // Set the page descriptor to free
    pheapDesc[ad] = 0;
}

// Allocate a block of page-aligned memory
char* pmalloc(size_t size) {
    // Loop through the available list
    for (int i = 0; i < MAX_PAGE_ALIGNED_ALLOCS; i++)
    {
        // If the page descriptor is 1, continue
        if (pheapDesc[i]) {
            continue; 
        }
    
        pheapDesc[i] = 1;                                                                       // Set the page descriptor to 1
        printf("PAllocated from 0x%x to 0x%x\n", pheapBegin + i*4096, pheapBegin + (i+1)*4096); // Print the allocation
        return (char *)(pheapBegin + i*4096);                                                   // Return the allocation
    }

    printf("pmalloc: FATAL: failure!\n"); // If the function has reached here then it has failed
    return 0;
}

// Allocate a block of memory
void* malloc(size_t size) {
    if(!size){
        return 0; // If the size is 0, return 0
    } 

    // Loop through blocks to find an available block with enough size
    uint8_t *memory = (uint8_t *)heapBegin;

    while ((uint32_t)memory < lastAlloc)
    {
        // Get the allocation and print the memory and allocation
        alloc_t *a = (alloc_t *)memory;
        printf("mem=0x%x a={.status=%d, .size=%d}\n", memory, a->status, a->size);

        // If size of the block is 0, jump to nalloc
        if (!a->size) {
            goto nalloc;
        }
            
        // True if the current memory block is allocated
        if (a->status) {
            memory += a->size;                  // Add the size of the allocated block 
            memory += sizeof(alloc_t);          // Add the size of the allocation struct
            memory += 4;                        // Add 4
            continue;
        }

        // If the block is not allocated and its size is big enough, adjust its size, set the status, and return the location.
        if (a->size >= size)
        {
            a->status = 1; // Set the status of the allocation to 1
            printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, memory + sizeof(alloc_t), memory + sizeof(alloc_t) + size); // Print the allocation
            memset(memory + sizeof(alloc_t), 0, size);                                                                            // Set the memory to 0
            memoryUsed += size + sizeof(alloc_t);                                                                                 // Increment the memory used
            return (char *)(memory + sizeof(alloc_t));                                                                            // Return the memory + the size of the allocation
        }

        // If the block is not allocated and its size is not big enough, add its size and the sizeof(alloc_t) to the pointer and continue.
        memory += a->size;
        memory += sizeof(alloc_t);
        memory += 4;
    }

    // If no available block is found, panic.
    nalloc:;
    if (lastAlloc + size + sizeof(alloc_t) >= heapEnd)
    {
        panic("Cannot allocate bytes! Out of memory.\n");
    }


    alloc_t *alloc = (alloc_t *)lastAlloc; // Set the allocation to the last allocation
    alloc->status = 1;                     // Set the status of the allocation to 1
    alloc->size = size;                    // Set the size of the allocation to the size

    lastAlloc += size;                     // Add the size to the last allocation
    lastAlloc += sizeof(alloc_t);          // Add the size of the allocation struct to the last allocation
    lastAlloc += 4;                        // Add 4

    printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(alloc_t), lastAlloc); // Print the allocation

    memoryUsed += size + 4 + sizeof(alloc_t);                       // Increment the memory used
    memset((char *)((uint32_t)alloc + sizeof(alloc_t)), 0, size);   // Set the memory to 0
    return (char *)((uint32_t)alloc + sizeof(alloc_t));             // Return the allocation + the size of the allocation
}


