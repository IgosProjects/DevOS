/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file handles PIC related actions(remapping masking and such)

#include <assembly/ports.h>

void RemapPIC() {
    // Set init mode
    outb(0x20, 0x10 | 0x1); // Master PIC
    outb(0xA0, 0x10 | 0x1); // Slave PIC

    // Set vector offsets
    outb(0x20, 0x08); // Master PIC
    outb(0xA0, 0x70); // Save PIC

    // Tell master PIC that there is a slave on IRQ2
    outb(0x20, 1 << 2); // Master PIC
    outb(0xA0, 2); // Slave PIC

    // Enable 8086 mode
    outb(0x20, 0x1); // Master PIC
    outb(0xA0, 0x1); // Slave PIC

    // Unmask the PICs
    outb(0x20, 0); // Master PIC
    outb(0xA0, 0); // Slave PIC
}