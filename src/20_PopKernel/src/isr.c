/* Adapted from the James Molloy's GDT/IDT implementation totorial at https://archive.is/L3pyA */

#include "libc/stdio.h"
#include "isr.h"
#include "io.h"

isr_t interruptHandlers[256];


void registerInterruptHandler(uint8_t n, isr_t handler) {
	interruptHandlers[n] = handler;
}

// This is a common handler for all ISR's that will simply print the interrupt number and info to the screen.
void isrHandler(registers_t regs) {
	

    // Calls the interrupt handler if there is one
    // This was not needed before as we simply printed the interrupt number corresponing exception message to the sceen
    // Now that we have added things like a custom page fault handler, we need to call it
    if (interruptHandlers[regs.intNum] != 0) {
		isr_t handler = interruptHandlers[regs.intNum];
		handler(regs);
   	}

	else {
		printf("Received interrupt: %d - %s\n", regs.intNum, exceptionMessages[regs.intNum]);
	}
}

// IRQ handler. Handles hardware interrupts
void irqHandler(registers_t regs) {
	
    // If the intNum is greater than or equal to 40, then we need to send an EOI to the slave controller
    if (regs.intNum >= 40) {
		outb(0xA0, 0x20);
    }

    // In either case, we need to send an EOI to the master interrupt controller too
    outb(0x20, 0x20);

    // Calls the interrupt handler if there is one
    if (interruptHandlers[regs.intNum] != 0) {
		isr_t handler = interruptHandlers[regs.intNum];
		handler(regs);
   }
}

