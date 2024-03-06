; Don't use

; Sources:
; https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
; page 34
; https://github.com/cfenollosa/os-tutorial/blob/master/09-32bit-gdt/32bit-gdt.asm

; Global Descriptor Table
gdt_start:

gdt_null:
    dd 0x0 ; dd means "double word", word means 2 bytes, so double word is 4 bytes
    dd 0x0

gdt_code:
    dw 0xffff ; Limit 16 bits. 0-15.
    dw 0x0 ; base 0-15.
    db 0x0 ; base 16-23. (db = double byte)

    ; bit 7: present. Set bit means it's in memory. Used for virtual memory.
    ; bit 6-5: privilege. Kernel is 00, user is 11.
    ; bit 4: descriptor type. Set bit means code, cleared bit means data.
    ; bit 3: Executable. Set bit means code, cleared bit means data.
    ; bit 2: Conforming (memory protection). Cleared bit means this segment cannot be accessed by lower privilege level segments.
    ; bit 1: Readable/Writable. Set bit means code segment is readable, data segment is writable.
    ; bit 0: Accessed. Set bit means CPU has accessed this segment.
    db 10011010b ; Type flags.

    ; bit 7: granularity. Set bit means limit is in 4kb blocks, cleared bit means limit is in bytes.
    ; bit 6: Size. Set bit means 32 bit protected mode, cleared bit means 16 bit protected mode.
    ; bit 5: Reserved. Set bit means reserved, cleared bit means 8086 mode.
    ; bit 4: Available for system use.
    ; bit 3-0: Limit 16-19.
    db 11001111b ; Limit flags (16-19)
    db 0x0 ; base 24-31.

    ; The data segment has the same setup as the previous code segment, except for a couple details.
    ; The type flags are initialized a little differently, and bit 2 has a different meaning.
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0

    ; bit 2: Direction. Set bit means data segment grows up, cleared bit means data segment grows down.
    db 10010010b ; Type flags.
    db 11001111b ; Limit flags (16-19)
    db 0x0

gdt_end: ; Mark the end of GDT so the assembler knows how big it is.

; Offer descriptor to CPU, not GDT itself.
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of GDT.
    dd gdt_start ; Start address of GDT.

; GDT constants
SEG_CODE equ gdt_code - gdt_start
SEG_DATA equ gdt_data - gdt_start

; Instruction to load GDT
lgdt [gdt_descriptor] ; Load GDT.