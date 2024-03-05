#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>

#include <gdt.h>
#include <function.h>

// Declare the GDT initialization function implemented in assembly
extern void init_gdt();

// Structure representing the Multiboot information
struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

// Declare the kernel_main function
int kernel_main();

// Entry point when the bootloader starts executing the kernel
int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    // Initialize the Global Descriptor Table (GDT)
    init_gdt();

    // Print "Hello World" to the console using printf-like function
    terminal_write("Hello World!");

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}