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
    int32_t numbers[] = {
        0,
        -123,
        77777,
        -293,
        123566,
        998202
    };

    for (size_t i = 0; i < array_size(numbers); i++)
    {
        monitor_write_sdec(numbers[i]);
        monitor_write("\n");
    }

    // Call cpp kernel_main (defined in kernel.cpp)
    return kernel_main();
}