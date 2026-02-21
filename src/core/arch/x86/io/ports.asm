; * This file is part of DevOS
; * 
; * Copyright© 2026 EyeDev
; * 
; * DevOS is free software: you can redistribute it and/or modify it under the
; * terms of the MIT License. See LICENSE for full details of all licenses
; * that apply to this repository.

; This is a small driver used for I/O accsses with ports. It provides inb, outb, inw and outw
; Yes it is very simple and yes it is very small

; GLOBAL FUNCTIONS

global outb
global inb
global outw
global inw

; Send a 8 bit value down a port
outb:
    mov dx, [esp+4] ; Read port argument into dx
    mov al, [esp+8] ; Read value argument into al
    out dx, al
    ret ; Return from function

; Read a 8 bit value from a port
inb:
    mov dx, [esp+4] ; Read port argument into dx
    in al, dx ; Read into al
    movzx eax, al
    ret ; Return from function


; Send a 16 bit value down a port
outw:
    mov dx, [esp+4] ; Read port value
    mov ax, [esp+8] ; Read value
    out dx, ax
    ret ; Return from function

; Read a 16 bit value from a port
inw:
    mov dx, [esp+4] ; Read port value
    in ax, dx
    ret ; Return from function