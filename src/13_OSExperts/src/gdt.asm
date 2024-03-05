global gdt_flush         ; Declare gdt_flush as a global symbol

gdt_flush:
    MOV eax, [esp+4]     ; Load the GDT address from the argument passed on the stack
    LGDT [eax]           ; Load the GDT with Load GDT instruction

    ; Set data segment (ds), extra segment (es), 
    ;fs, gs, and stack segment (ss) registers
    MOV ax, 0x10         ; 0x10 is the selector for the data segment
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    MOV ss, ax

    JMP 0x08:.flush     ; Jump to the 32-bit code segment (0x08) to start executing
.flush:
    RET                 ; Return from the gdt_flush function