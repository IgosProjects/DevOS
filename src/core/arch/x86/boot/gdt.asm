; * This file is part of DevOS
; * 
; * Copyright© 2026 EyeDev
; * 
; * DevOS is free software: you can redistribute it and/or modify it under the
; * terms of the MIT License. See LICENSE for full details of all licenses
; * that apply to this repository.

; This is the GDT, you may be wondering: "But GRUB gives us a GDT?"
; Well that GDT is not a full one, its basic scafolding until you make an actual GDT

GDTStart:
    ; The GDT starts with 8 null bytes
    dd 0x0 ; 4 bytes
    dd 0x0 ; 4 bytes

; GDT code segment
GDTCode:
    dw 0xffff ; Segment lenght
    dw 0x0 ; Segment base
    db 0x0 ; Segment base
    db 10011010b ; Flags(8 bits)
    db 11001111b ; Flags(4 bits) + segment lenght
    db 0x0 ; Segment base

; Identical to GDTCode, but flags have changed
GDTData:
    dw 0xffff ; Segment lenght
    dw 0x0 ; Segment base
    db 0x0 ; Segment base
    db 10010010b ; Flags(8 bits)
    db 11001111b ; Flags(4 bits) + segment lenght
    db 0x0 ; Segment base

GDTEnd:
    ; NOTE: Must contain nothing

global GDTDescriptor
GDTDescriptor:
    dw GDTEnd - GDTStart - 1 ; Size, allways 1 less
    dd GDTStart ; Address

global CODE_SEG
global DATA_SEG

; Define segments for later use
CODE_SEG equ GDTCode - GDTStart
DATA_SEG equ GDTData - GDTStart