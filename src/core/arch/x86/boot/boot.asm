; * This file is part of DevOS
; * 
; * Copyright© 2026 EyeDev
; * 
; * DevOS is free software: you can redistribute it and/or modify it under the
; * terms of the MIT License. See LICENSE for full details of all licenses
; * that apply to this repository.

; This is boot.asm, it is ran AFTER grub loads and runs our kernel
; In here we define a multiboot2 header and setup a stack(this is important as C uses the stack heavly)
; After that we jump to C

[BITS 32] ; We are in 32 bit protected mode

section .multiboot2
align 8

    ; Do not remove the labels they are used to compute size
HeaderStart:
    dd 0xE85250D6 ; Multiboot2 magic number
    dd 0 ; Architecture(0 is x86)
    dd HeaderEnd - HeaderStart ; Compute size

    ; Multiboot2 checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (HeaderEnd - HeaderStart))

    ; Since multiboot2 uses tags to reqest framebuffer and such, we need a end tag.
    ; A end tag is used so GRUB doesnt read unallocated memory

    ; End tag
    dw 0    ; Type
    dw 0    ; Flags
    dd 8    ; Size
HeaderEnd:

section .text ; Now lets get onto the fun part.. CODING!!
global start ; This will let GRUB see our start function

extern StartKernel
extern Halt ; Defined in "cpu.asm"
extern GDTDescriptor ; Defined in "gdt.asm"
extern CODE_SEG

start:
    cli ; Disable interrupts(prevent them from firing so we dont crash)

    lgdt [GDTDescriptor] ; Load GDT
    jmp CODE_SEG:.flush_cs

; NOTE: This function is just used to set CS afterwards, dont remove it!
; We do a far jump for a reason
.flush_cs:
    mov esp, stack_top ; Set the stack pointer

    mov ax, 0x10
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Now that we have a stack, we can jump to C code
    call StartKernel ; Jump to the kernel
    
    ; If kernel returns halt forever
    call Halt
    

; BSS is uninitilized memory
; We can use it to store stuff
section .bss
align 16
stack_bottom:
    resb 16384
stack_top: