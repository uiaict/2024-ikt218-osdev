//code is based on examples from the course materials - especially session 6 and copilot. 

#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include "libc/multiboot2.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/gdt.h"

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


//basic printfunction 
    void write_string(int colour, const char *string) 
    {
        volatile char *video = (volatile char*)0xb8000;
        while(*string != 0) {
            *video++ = *string++;
            *video++ = colour;
        }

    }

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

// Check the magic number
    /*if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        // Magic number is invalid
        //write_string(0x0F, "Invalid magic number");
    } else {*/

    // Initialize the GDT
    init_gdt();
    
    // defines the parameters in the print function above and prints "Hello, World!" in white text on a black background
    
    const char *hello_world = "Hello, World!";
    int colour = 0x0F; // White text, black background
    write_string(colour, hello_world);    
    

    return kernel_main();
    }    

    // Call cpp kernel_main (defined in kernel.cpp)
    