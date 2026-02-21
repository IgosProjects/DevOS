; * This file is part of DevOS
; * 
; * Copyright© 2026 EyeDev
; * 
; * DevOS is free software: you can redistribute it and/or modify it under the
; * terms of the MIT License. See LICENSE for full details of all licenses
; * that apply to this repository.

global Halt
global LoadNewIDT
global GenericISRHandler

; Halts the entire system forever
Halt:
    cli
    .hltloop:
        hlt
    
LoadNewIDT:
    lidt [esp+4] ; Load first argument as IDT
    ret

GenericISRHandler:
    cli
    pushad

    ; Push registers
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10 ; Kernel code segment
    mov ds, ax
    mov es, ax

    push 0 ; Push error code
    push 0 ; Push interrupt

    popad

    ; Push registers
    pop ds
    pop es
    pop fs
    pop gs

    sti ; Enable interrupts