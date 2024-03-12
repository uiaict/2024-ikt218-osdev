extern "C" {
    #include "libc/stdint.h"
    #include "libc/stddef.h"
    #include "libc/stdio.h"
    #include "libc/stdbool.h"
    #include "libc/stdlib.h"
    #include "libc/string.h"
    #include "pit.h"
    #include "io.h"
    #include "macros.h"
}

#include "applications/demos.h"
#include "applications/song.h"


// Demonstrates the printf function
void printDemo() {
    // Creates test variables to be used for printf testing
    char strTest[] = "Hello World!";                
    int intTest = 123;
    unsigned int uintTest = 1234567890;
    float floatTest = 3.14;
    double doubleTest = 3.14159;
    char hexTest[] = "0x01";

    // Prints the test variables
    printf("Printing a string: %s\n", strTest);     
    printf("Printing an integer: %d\n", intTest);
    printf("Printing an unsigned integer: %u\n", uintTest);
    printf("Printing a float: %f\n", floatTest);
    printf("Printing a float with .1f precition: %.1f\n", floatTest);
    printf("Printing a double: %f\n", doubleTest);
    printf("Printing a hex: %s\n", hexTest);    
}

// Demo showing the sleep function using the PIT
void pitDemo() {
    printf("Using interrupt to sleep in ten intervals of 1sec\n");
    for (int i = 1; i < 10; i++) {
        printf("%dsec\n", i);
        sleepInterrupt(1000);
    }
    printf("Ahhhhhh. What a great nap!\n");
}

// Triggers interrupts to demonstrate the interrupt handler
void isrDemo() {
    asm volatile("int $0x00");
    asm volatile("int $0x01");
    asm volatile("int $0x02");
    asm volatile("int $0x03");
    asm volatile("int $0x04");
    asm volatile("int $0x05");
    asm volatile("int $0x06");
    asm volatile("int $0x07");
    asm volatile("int $0x08");
    asm volatile("int $0x09");
    asm volatile("int $0x0A");
    asm volatile("int $0x0B");
    asm volatile("int $0x0C");
    asm volatile("int $0x0D");
    printf("Skipping page fault as this causes panic\n");
    asm volatile("int $0x0F");
    asm volatile("int $0x10");
    asm volatile("int $0x11");
    asm volatile("int $0x12");
    asm volatile("int $0x13");
    asm volatile("int $0x14");
    asm volatile("int $0x15");
    asm volatile("int $0x16");
    printf("Interrupts are working!\n");

}

// Causes a page fault to demonstrate the page fault handler
void pageFaultDemo() {
    printf("Running page fault demo causes a panic. Do you want to continue [y/n]\n");
    char c = getchar();
    // Clears the y/n input
    videoMemory[cursorPos] = ' ';
    cursorPos -= 2;
    // Runs or aborts the page fault demo
    if (c == 'y'){
        uint32_t *ptr = (uint32_t*)0xE0000000;
        uint32_t do_page_fault = *ptr;
    } else {
        printf("Aborted\n");
    }
}


// Changes the color of the text or background
void changeColorDemo() {
    printf("Do you want to change the color of the text or background? [t/b]\n");
    char c = getchar();
    // Clears the input
    videoMemory[cursorPos] = ' ';
    cursorPos -= 2;

    int color;
    printf("Enter the color you want to change to:\n");
    printf("0. Black\n");
    printf("1. Blue\n");
    printf("2. Green\n");
    printf("3. Cyan\n");
    printf("4. Red\n");
    printf("5. Magenta\n");
    printf("6. Brown\n");
    printf("7. Light Grey\n");
    printf("8. Dark Grey\n");   
    printf("9. Light Blue\n");
    printf("10. Light Green\n");
    printf("11. Light Cyan\n");
    printf("12. Light Red\n");
    printf("13. Light Magenta\n");
    printf("14. Light Brown\n");
    printf("15. White\n");
    scanf("%d", &color);
    videoMemory[cursorPos] = ' ';
    cursorPos -= 2;

    if (c == 't'){
        changeTextColor(color);
    } else {
        changeBackgroundColor(color);
    }
}

// Changes the cursor
void changeCursorDemo() {
    printf("Type 'up' to get a vertical cursor and 'down' to get a horizontal cursor.\n");
    printf("Type 'disable' to disable the cursor.\n");
    char cursorChoice[10];
    scanf("%s", cursorChoice);
    if (strcmp(cursorChoice, "up") == 0){
        cursorVertical;
    } else if (strcmp(cursorChoice, "down") == 0){
        cursorHorizontal;
    } else if (strcmp(cursorChoice, "disable") == 0){
        disableCursor();
    } else {
        printf("Invalid input\n");
    }
}

