#include <../include/terminal_write.h>
#include <../include/libc/stdint.h>
#define width 80
#define height 25

uint16_t *const vga = (uint16_t *const)0xB8000;
int col, row = 0;

void terminal_write(const char *string){
    char *ptr = string;

    do{
        vga[row * width + col] = *ptr | 0x0700;
        col++;
        *ptr++;
    }while(*ptr != 0x00);

    return;
}
