/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This is the ATA driver, it handles ATA disk reads
/* FUN FACT: IDE is not the protcol, its the electrical signals on the wires
   ATA is the actual standard
*/

#include <stdint.h>
#include <drivers/disk/ata.h>
#include <assembly/ports.h>

// Read a sector from the master ATA drive
void ReadSectorATA(uint32_t sector, uint16_t* buffer) {
    outb(0x1F6, 0xE0 | ((sector >> 24) & 0x0F));
    outb(0x1F2, 1);
    outb(0x1F3, sector & 0xFF);
    outb(0x1F4, (sector >> 8) & 0xFF);
    outb(0x1F5, (sector >> 16) & 0xFF);
    outb(0x1F7, 0x20); // Send read command

    while (1) {
        uint8_t status = inb(0x1F7); // Get status from drive
        if (!(status & 0x80) && (status & 0x08)) break; // Wait until the BSY bit is clear and the DRQ bit is on
    }

    // This will only run if we recived the data from the drive
    for (int i = 0; i < 256; i++) {
        buffer[i] = inw(0x1F0); // Get data from drive, and put it into the buffer
    }
}