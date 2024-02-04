#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdio.h"
#include "libc/stdbool.h"
#include "libc/stdlib.h"
#include <multiboot2.h>
#include "gdt.h"
#include "io.h"
#include "macros.h"




struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    
    initGdt(); // Initialize the GDT
    
    cursorVertical; // Makes the cursor vertical

    char strTest[] = "Hello World!"; 
    char charTest = 'a';
    int posIntTest = 9598;
    int negIntTest = -9598;
    unsigned int uintTest = 42949672945;
    float floatTest = 224.842;

    // Prints the different types of data to the screen
    printf("String: %s\n", strTest);
    printf("Character: %c\n", charTest);
    printf("Positive Integer: %d\n", posIntTest);
    printf("Negative Integer: %d\n", negIntTest);
    
    printf("Unsigned Integer: %u\n", uintTest);
    printf("Float: %f\n", floatTest); 
    printf("Float with 2 decimal places: %.2f\n", floatTest);

    // Changes the background and text color for all previous and future characters. 
    // If you want to change for future prints only change the currentTextColor and currentBackgroundColor directly
    changeBackgroundColor(vgaColorDarkGrey); 
    changeTextColor(vgaColorWhite); 

    return kernel_main(); // Call the kernel_main function1
}