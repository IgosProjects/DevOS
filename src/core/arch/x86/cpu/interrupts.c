/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file handles interrupts and other stuff
// It uses the "pic.c" and "idt.c" files to work correctly!!

#include <kernel/cpu/idt.h>
#include <kernel/cpu/pic.h>
#include <kernel/cpu/cpu.asm.h>

void InitInterrupts() {
    RemapPIC(); // Remap the PIC, see "https://wiki.osdev.org/8259_PIC" for more info
    InitIDT(); // Initilize the Interrupt Descriptor Table

    SetIDTEntry(0, (uint32_t)GenericISRHandler); // Interrupt 0 is "Divide By Zero"

    LoadIDT();
}
