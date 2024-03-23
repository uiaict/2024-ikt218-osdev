#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include "stdtxt.h"
#include "gdt.h"
#include "idt.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    gdtInitialize();
    idtInitialize();
    initScreen(); // Clear screen and initialize memory buffer for text.

    printString("Hello, World!\n");

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}