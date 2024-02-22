global gdt_flush

gdt_flush:
    MOV eax, [esp+4]
    LGDT [eax]

    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    MOV ss, ax
    JMP 0x08:.flush
.flush:
    RET    