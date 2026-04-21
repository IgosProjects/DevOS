/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

#include <stdint.h>
#include <assembly/ports.h>
#include <drivers/debug/serial.h>

static inline int IsSerialReady() {
    return inb(COM1 + 5) & 0x20; // THR empty?
}

// Initilizes the serial driver, allows for debugging
void InitSerial() {
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // Divisor low
    outb(COM1 + 1, 0x00); // Divisor high
    outb(COM1 + 3, 0x03); // 8 bits, no parity and one stop bit

    outb(COM1 + 2, 0xC7); // Enable FIFO

    outb(COM1 + 4, 0x0B); // Enable IRQs
}

// Writes a single character to serial COM1
void WriteSerialChar(char Character) {
    while (!IsSerialReady()); // Wait until serial is ready
    outb(COM1, Character); // Print to serial
}