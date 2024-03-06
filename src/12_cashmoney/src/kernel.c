#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include "monitor.h"

struct multiboot_info
{
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info* mb_info_addr)
{
    const int32_t number = 123456789;
    monitor_write("Number: ");
    monitor_write_udec(number);
    monitor_write(", in hex: 0x75BCD15\n");
    monitor_write("monitor_write_hex result: ");
    monitor_write_hex(number);
    monitor_write("\n");

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}