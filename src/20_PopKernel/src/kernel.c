#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/stdbool.h"
#include "libc/stdlib.h"
#include <multiboot2.h>
#include "desTables.h"
#include "isr.h"
#include "io.h"
#include "macros.h"
#include "keyboard.h"
#include "memory.h"
#include "kernelUtils.h"
#include "pit.h"
#include "applications/frequencies.h"

extern uint32_t end; 


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
   
  	initDesTables();                                // Initializes the descriptor tables
    initKeyboard();                                 // Initializes the keyboard
    initPit();                                      // Initializes the PIT 
    initKernelMemory(&end);                         // Initializes the kernel memory
    initPaging();                                   // Initializes the paging
    printMemoryLayout();                            // Prints the memory layout

    cursorVertical;                                 // Makes the cursor vertical
    changeBackgroundColor(vgaColorDarkGrey);        // Changes the background color to dark grey
    changeTextColor(vgaColorWhite);                 // Changes the text color to white

    return kernel_main();                           // Call the kernel_main function
}