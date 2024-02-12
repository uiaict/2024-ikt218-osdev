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


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();


int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
   
  	initDesTables(); // Initializes the descriptor tables
    initKeyboard(); // Initializes the keyboard

    cursorVertical; // Makes the cursor vertical
    changeBackgroundColor(vgaColorDarkGrey); 
    changeTextColor(vgaColorWhite); 

    char strTest[] = "Hello World!"; 

    // Prints the different types of data to the screen
    //printf("%s\n", strTest);



    return kernel_main(); // Call the kernel_main function1
}