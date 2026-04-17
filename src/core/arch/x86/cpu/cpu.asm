; * This file is part of DevOS
; * 
; * Copyright© 2026 EyeDev
; * 
; * DevOS is free software: you can redistribute it and/or modify it under the
; * terms of the MIT License. See LICENSE for full details of all licenses
; * that apply to this repository.

global Halt
global LoadNewIDT

extern ISRHandler
extern IRQHandler

; Halts the entire system forever
Halt:
    cli
    .hltloop:
        hlt
        jmp .hltloop
    
LoadNewIDT:
    lidt [esp+4] ; Load first argument as IDT
    ret

; ===================================== BEWARE =====================================
; Emotinal damage below(alot of it!)

; Stub called by all ISR handler
ISRStub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, ISRHandler
    call eax
    add esp, 4
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

IRQStub:
    cld
    call IRQHandler ; Call the C handler
    add esp, 8
    iret ; Return from interrupt

; im allready emotinally damaged, pls send help

; These are ISRs that dont push a error code allready
%macro ISR_NOCODE 1
    isr%1:
        push dword 0 ; Push fake error code
        push dword %1 ; Push interrupt number
        jmp ISRStub
%endmacro

; These are ISRs that push an error code allready
%macro ISR_CODE 1
    isr%1:
        ; Dont push a code
        push dword %1 ; Push interrupt number
        jmp ISRStub
%endmacro

; GLOBALS
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

ISR_NOCODE 0 ; Divide by zero
ISR_NOCODE 1 ; Debug
ISR_NOCODE 2 ; Non maskable interrupt
ISR_NOCODE 3 ; Breakpoint
ISR_NOCODE 4 ; Detected overflow
ISR_NOCODE 5 ; Out of bounds
ISR_NOCODE 6 ; Invalid opcode
ISR_NOCODE 7 ; No coprocessor
ISR_CODE 8 ; Double fault
ISR_NOCODE 9 ; Copressor segment overrun
ISR_CODE 10 ; Bad TSS
ISR_CODE 11 ; Segment not present
ISR_CODE 12 ; Stack fault
ISR_CODE 13 ; General protection fault
ISR_CODE 14 ; Page fault
ISR_NOCODE 15 ; Unknown interrupt
ISR_NOCODE 16 ; Coprocessor fault
ISR_CODE 17 ; Aligment check
ISR_NOCODE 18 ; Machine check
ISR_NOCODE 19
ISR_NOCODE 20
ISR_CODE 21
ISR_NOCODE 22
ISR_NOCODE 23
ISR_NOCODE 24
ISR_NOCODE 25
ISR_NOCODE 26
ISR_NOCODE 27
ISR_NOCODE 28
ISR_NOCODE 29
ISR_NOCODE 30
ISR_NOCODE 31

; These are ISRs that dont push a error code allready
%macro IRQ 1
    irq%1:
        push dword 0 ; Push fake error code
        push dword %1+32 ; Push interrupt number(add 32 cause IRQs start at interrupt 32)
        jmp IRQStub
%endmacro

; GLOBALS
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15