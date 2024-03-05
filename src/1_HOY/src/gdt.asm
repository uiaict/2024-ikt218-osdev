[GLOBAL gdt_flush]

gdt_flush:
    mov eax, [esp+4]
    lgdt [eax] ; Load the new GDT pointer
    mov ax, 0x10 ; Load the data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush ; Far jump to refresh the CPU's cache for the code segment
.flush:
    ret ; Return to the caller