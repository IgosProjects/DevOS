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

    // Save masks
    uint8_t MaskMaster = inb(0x21);
    uint8_t MaskSlave = inb(0xA1);

    // Set init mode
    outb(0x20, 0x10 | 0x1); // Master PIC
    outb(0xA0, 0x10 | 0x1); // Slave PIC

    // Set vector offsets
    outb(0x21, 0x20); // Master PIC
    outb(0xA1, 0x28); // Slave PIC

    // Tell master PIC that there is a slave on IRQ2
    outb(0x21, 1 << 2); // Master PIC
    outb(0xA1, 2); // Slave PIC

    // Enable 8086 mode
    outb(0x21, 0x1); // Master PIC
    outb(0xA1, 0x1); // Slave PIC

    // Restore masks
    outb(0x21, MaskMaster); // Master PIC
    outb(0xA0, MaskSlave); // Slave PIC
    
    // Mask PIC
    // uint8_t mask = inb(0x21);   // read current master PIC mask
    // mask |= 0x01;              // set bit 0 (IRQ0)
    // outb(0x21, mask);          // write back
}