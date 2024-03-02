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

    char strTest[] = "Hello World!";                // Creates test variables to be used for printf testing
    int intTest = 123;
    unsigned int uintTest = 1234567890;
    float floatTest = 3.14;
    double doubleTest = 3.14159;
    char hexTest[] = "0x01";

    // Trigger page fault intentionally
/*     uint32_t *ptr = (uint32_t*)0xE0000000;
    uint32_t do_page_fault = *ptr; */

 
    return kernel_main(); // Call the kernel_main function
}