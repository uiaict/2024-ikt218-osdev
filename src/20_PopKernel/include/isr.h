/* Adapted from the James Molloy's GDT/IDT implementation totorial at https://archive.is/L3pyA */

#ifndef ISR_H
#define ISR_H

#include "libc/stdint.h"

#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

typedef struct registers {
	uint32_t ds;  // Data segment selector
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  // Register states
	uint32_t intNum, errCode;  // Interrupt number and error code
	uint32_t eip, cs, eflags, useresp, ss;  // Instruction pointer, code segment selector, flags, stack pointer, and stack segment selector
} registers_t;

typedef void (*isr_t)(registers_t); // Define a type for interrupt service routines
void registerInterruptHandler(uint8_t n, isr_t handler); // Registers an interrupt handler

// Gives more info on the interrupt
static const char *exceptionMessages[] = {
	"Division By Zero",
	"Debug",
	"Non Maskable Interrupt",
	"Breakpoint",
	"Into Detected Overflow",
	"Out of Bounds",
	"Invalid Opcode",
	"No Coprocessor",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Bad TSS",
	"Segment Not Present",
	"Stack Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown Interrupt",
	"Coprocessor Fault",
	"Alignment Check",
	"Machine Check"
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Control Protection Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Hypervisor Injection Exception",
	"VMM Communication Exception",
	"Reserved" 
};

#endif