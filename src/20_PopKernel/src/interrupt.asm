;Adapted from the James Molloy's GDT/IDT implementation totorial at https://archive.is/L3pyA
;The ISR stubs are defined here. The ISR stubs are the entry points for each interrupt service routine. 
;They are responsible for saving the state of the CPU, and then calling the C handler for the interrupt.
;If we dont save the state of the CPU we could get weird bugs. Rund saveStateTest() from main to see that the state is saved correctly.

; Macro for Interrupt Service Routine (ISR)
%macro ISR 1
[GLOBAL isr%1]         ; Declare a global symbol for the ISR
isr%1:                 ; Label for the ISR
    cli                ; Clear interrupts to prevent preemption
    push byte 0        ; Push a dummy error code on the stack
    push byte %1       ; Push the interrupt number on the stack
    jmp isrCommonStub  ; Jump to the common ISR handler
%endmacro

; Macro for Interrupt Service Routine (ISR) with error code
; Added now since we have custom handling for page faults
%macro ISR_ERRORCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isrCommonStub
%endmacro

; Macro for Interrupt Request (IRQ)
%macro IRQ 2
[GLOBAL irq%1]         ; Declare a global symbol for the IRQ
irq%1:                 ; Label for the IRQ
    cli                ; Clear interrupts to prevent preemption
    push byte 0        ; Push a dummy error code on the stack
    push byte %2       ; Push the interrupt number on the stack
    jmp irqCommonStub  ; Jump to the common IRQ handler
%endmacro


; Defines the ISR stubs
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR_ERRORCODE 14        ; Page fault gives an error code. Since we now have custom handling for page faults, we need to handle the error code
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19
ISR 20
ISR 21
ISR 22
ISR 23
ISR 24
ISR 25
ISR 26
ISR 27
ISR 28
ISR 29
ISR 30
ISR 31

; Defines the IRQ stubs
IRQ  0,	32
IRQ  1,	33
IRQ  2,	34
IRQ  3,	35
IRQ  4,	36
IRQ  5,	37
IRQ  6,	38
IRQ  7,	39
IRQ  8,	40
IRQ  9,	41
IRQ 10,	42
IRQ 11,	43
IRQ 12,	44
IRQ 13,	45
IRQ 14,	46
IRQ 15,	47

; Common ISR handler
[EXTERN isrHandler]    
isrCommonStub:
    pusha                     ; Push all the general purpose registers onto the stack to save their state

    mov ax, ds                ; Move the value of the data segment register into ax
    push eax                  ; Push the value of ax onto the stack

    mov ax, 0x10              ; Load kenrel data segment descriptor into ax 
    mov ds, ax                
    mov es, ax               
    mov fs, ax             
    mov gs, ax               

    call isrHandler           ; Call the ISR handler

    pop eax                   ; Reload to restore state
    mov ds, ax               
    mov es, ax             
    mov fs, ax              
    mov gs, ax              

    popa                      
    add esp, 8                
    sti                      
    iret                    
    
; Common IRQ handler
[EXTERN irqHandler]
irqCommonStub:
    pusha                   ; Push all the general purpose registers onto the stack to save their state

    mov ax, ds              ; Move the value of the data segment register into ax
    push eax                ; Push the value of ax onto the stack

    mov ax, 0x10            ; Load kenrel data segment descriptor into ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irqHandler         ; Call the IRQ handler    

    pop ebx                 ; Reload to restore state
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                    
    add esp, 8     
    sti
    iret          