#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <gdt.h>
#include <multiboot2.h>
#include <../include/terminal_write.h>

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {

    iniGdt();
    terminal_write("Hello World!");

    return kernel_main();
}