#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <multiboot2.h>


struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};


void main(uint32_t magic, struct multiboot_info* mb_info_addr) {

}