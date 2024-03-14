#include "../include/libc/stdio.h"
#include "../gdt/gdt.h"


extern "C" int kernel_main(void);
int kernel_main(){

    printf("Hello, World!\n\n");
    
    gdt_init();
   
    return 0;
}