#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

// 5_OsExp functions
void initScreen(void);
void putString(unsigned char *string);

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    initScreen(); // Clear screen and initialize memory buffer for text.

    putString((unsigned char *)"Hello, World!\n");

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}