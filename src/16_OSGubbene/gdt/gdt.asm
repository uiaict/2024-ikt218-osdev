
; gdt_flush.asm based on: https://wiki.osdev.org/GDT_Tutorial - Reload segment registers - Protected mode

[GLOBAL gdt_flush] 

gdt_flush:
    ; Load the GDT pointer
    lgdt [eax]

    ; Update the segment registers
    mov ax, 0x10  ; Value of the data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Jump to the code segment
    jmp 0x08:return  ; 0x08 is the value of the code segment selector

return:
    ret