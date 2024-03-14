extern main

global _start

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
    hlt ; Ensures the program does not continue executing random memory for example main again as it did without hlt

section .bss
stack_bottom:
    resb 4096 * 16
stack_top: