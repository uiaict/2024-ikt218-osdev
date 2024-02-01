; Define a loop that immediately jumps to byte 511, reads it and byte 512 to look for the 'magic number'.
loop:
    jmp loop

times 510-($-$$) db 0

dw 0xaa55 ; The magic number