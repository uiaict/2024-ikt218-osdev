#include "pit.h"
#include "isr.h"
#include "io.h"


volatile uint32_t tick = 0;                      // The number of PIT ticks

// The PIT handler
void pitHandler(registers_t regs) {
    tick++;                                      // Increment the number of ticks
}

// Returns the current tick
uint32_t getCurrentTick() {
    return tick;
}

// Initializes the PIT
void initPit() {

    outb(PIT_CMD_PORT, 0x36);                    // Send the command byte to the PIT
    outb(PIT_CHANNEL0_PORT, DIVIDER & 0xFF);     // Low byte of divisor
    outb(PIT_CHANNEL0_PORT, DIVIDER >> 8);       // High byte of divisor

    registerInterruptHandler(IRQ0, &pitHandler); // Register the PIT handler
}

// These sleep functions are based on the pseudo code provided by Per-Arne Andersen at https://perara.notion.site/Assignment-4-Memory-and-PIT-83eabc342fd24b88b00733a78b5a86e0 

// Sleeps using busy-waiting
void sleepBusy(uint32_t ms) {
    uint32_t startTick = getCurrentTick();      // Get the current tick
    uint32_t ticksToWait = ms * TICKS_PER_MS;   // Calculate the number of ticks to wait
    uint32_t endTick = startTick + ticksToWait; // Calculate the end tick

    if (endTick < startTick) {                  // If an overflow is expected
        
        while (getCurrentTick() >= startTick) { // Sleep until the overflow
            // Do nothing (busy wait)
        }
        while (getCurrentTick() < endTick) {    // Sleep until the end tick after the overflow
            // Do nothing (busy wait)
        }
    } else {                                    // If no overflow is expected
        while (getCurrentTick() < endTick) {
            // Do nothing (busy wait)
        }
    }
}

// Sleeps using interrupts
void sleepInterrupt(uint32_t ms) {
    uint32_t startTick = getCurrentTick();      // Get the current tick
    uint32_t ticksToWait = ms * TICKS_PER_MS;   // Calculate the number of ticks to wait
    uint32_t endTick = startTick + ticksToWait; // Calculate the end tick

    if (endTick < startTick) {                         // If an overflow is expected
        
        while (getCurrentTick() >= startTick) {        // Sleep until the overflow
            asm volatile (
                "sti\n\t"                              // Enable interrupts
                "hlt\n\t"                              // Halt the CPU until the next interrupt
            );
        }
        while (getCurrentTick() < endTick) {           // Sleep until the end tick after the overflow
            asm volatile (
                "sti\n\t"                              // Enable interrupts
                "hlt\n\t"                              // Halt the CPU until the next interrupt
            );
        }
    } else {                                           // If no overflow is expected
        while (getCurrentTick() < endTick) {
            asm volatile (
                "sti\n\t"                              // Enable interrupts
                "hlt\n\t"                              // Halt the CPU until the next interrupt
            );
        }
    }
}

