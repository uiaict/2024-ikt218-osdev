; Don't use

; SOURCE:
; 05.03
; https://medium.com/@jshschiavone/an-introduction-to-i386-boot-loader-programming-823354b80846

[org 0x7C00]        ; Master Boot Record address

mov si, STR         ; Store string
call _printf        ; Print string

jmp $

;;

_printf:
    pusha           ; Everything pushed onto stack in 16-bit mode
    
    ; Loop over characters until we encounter null
    str_loop:
        mov al, [si]    ; Move first char of si to lower nibble of al
        cmp al, 0       ; look for null
        jne print_char
        popa            ; pop all values off the stack
        ret             ; return 

    ; 
    print_char:
        mov ah, 0x0E    ; Call BIOS and shift cursor forward
        int 0x10        ; interrupt
        add si, 1       ; increment memory location pointer by 1
        jmp str_loop    ; jump to str_loop

STR: db `Successfully loaded bootsector`, 0x0A, 0x0D, 0