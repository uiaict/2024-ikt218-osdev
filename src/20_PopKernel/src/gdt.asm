; Adapted from the James Molloy's GDT implementation totorial at https://archive.is/L3pyA

[GLOBAL gdtFlush]    ; Allows the C code to call the asm function

gdtFlush:
   mov eax, [esp+4]  ; Get the pointer to the GDT
   lgdt [eax]        ; Loads the GDT pointer from the EAX register

   mov ax, 0x10      ; The value 0x10 is the offset in the GDT to our data segment. This line moves the value 0x10 into the AX register
   mov ds, ax        ; Loads the data segment register with the value in the AX register
   mov es, ax        ; Loads the extra segment register with the value in the AX register
   mov fs, ax        ; Loads the fs segment register with the value in the AX register
   mov gs, ax        ; Loads the gs segment register with the value in the AX register
   mov ss, ax        ; Loads the stack segment register with the value in the AX register
   jmp 0x08:.flush   ; Far jump to the code segment 0x08:flush. This will reload all the segment registers and flush the previous instruction cache
.flush:
   ret               ; Return from the function