#include "kernelUtils.h"

// Kernel panic function
void panic(const char *message)
{
    // Print the panic message
    printf("Kernel panic: %s\n", message);

    // Halt the CPU
    asm volatile("cli; hlt");
}