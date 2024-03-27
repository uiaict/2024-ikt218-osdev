#pragma once

#include "../common.h"

typedef struct
{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed)) gdt_entry_t;

// Pointer to GDT
typedef struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed)) gdt_ptr_t;

// A struct describing an interrupt gate.
typedef struct
{
   uint16_t base_low;             // The lower 16 bits of the address to jump to when this interrupt fires.
   uint16_t select;                 // Kernel segment selector.
   uint8_t  always0;             // This must always be zero.
   uint8_t  flags;               // More flags. See documentation.
   uint16_t base_high;             // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;

// Pointer to IDT
typedef struct idt_ptr_struct
{
   uint16_t limit;
   uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;

enum MODE_VALUE
{
   KERNEL_MODE,
   USER_MODE,
};

// Addresses of our ASM ISR handlers.
extern void isr0();
extern void isr1();
extern void isr2();

void init_descriptor_tables();