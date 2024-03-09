extern main
extern gp            ; gp the special pointer is in another file

global _start
global gdt_flush     ; Enables C code to link to this

section .multiboot_header
header_start:
    dd 0xe85250d6 	                                                ; Magic number (multiboot 2)
    dd 0				                                            ; Architecture 0 (protected mode i386)
    dd header_end - header_start 	                                ; Header length
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum

;align 8
;framebuffer_tag_start:
;    dw 5                                              ; type
;    dw 1                                              ; flags
;    dd framebuffer_tag_end - framebuffer_tag_start    ; size
;    dd 800                                            ; width
;    dd 600                                            ; height
;    dd 32                                             ; depth
;framebuffer_tag_end:

align 8
    ; Required end tag:
    dw 0	; type
    dw 0	; flags
    dw 8	; size
header_end:

section .text
bits 32

_start:
    cli

    mov esp, stack_top

	push ebx
	push eax

    call main ; Jump main function

gdt_flush:
    lgdt [gp]          ; Load the GDT with our 'gp'
    mov ax, 0x10        ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2     ; Far jump to refresh code segment
flush2:
    ret                 ; Return to C code


section .bss
stack_bottom:
    resb 4096 * 16
stack_top: