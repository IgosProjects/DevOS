/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file sets up the IDT(Interrupt Descriptor Table)
// It is used to tell the CPU where to go upon an interrupt

// It contains interrupt entires. It holds 256 interrupt entires.

#include <stdint.h>
#include <kernel/devos.h>
#include <kernel/cpu/cpu.asm.h>

// An 32 bit IDT entry looks like this
typedef struct __attribute__((packed)) IDTEntry {
    uint16_t offset_low; // Lower 16 bits of handler address
    uint16_t selector; // Code segment selector in GDT
    uint8_t  zero; // Allways suposed to be 0
    uint8_t  type_attr; // Entry types and atributes
    uint16_t offset_high; // Upper 16 bits of handler address
} IDTEntry;

// An IDT pointer looks like this
typedef struct __attribute__((packed)) IDTPtr {
    uint16_t limit; // Size of IDT - 1
    uint32_t base; // Address of first entry
} IDTPtr;

IDTEntry IDTTable[256]; // Create a IDT table with 256 entries
IDTPtr IDTPointer; // Pointer to the IDT table

// Set an IDT table entry
void SetIDTEntry(int index, uint32_t handler) {
    IDTTable[index].offset_high = High16(handler);
    IDTTable[index].selector = 0x8;
    IDTTable[index].type_attr = 0x8E; // Example flags and type
    IDTTable[index].zero = 0; // Allways meant to be zero
    IDTTable[index].offset_low = Low16(handler);
}

// Setup the IDT
void InitIDT() {
    // Setup entries
    SetIDTEntry(0, (uint32_t)GenericISRHandler);
    SetIDTEntry(32, (uint32_t)GenericISRHandler); // Timer IRQ
}

void LoadIDT() {
    // Update IDTPointer(moved due to size being 0 originally)
    IDTPointer.base = (uint32_t)&IDTTable;
    IDTPointer.limit = 256 * sizeof(IDTEntry) - 1;

    // Simple hardcode to debug issue
    asm volatile("lidt (%0)" : : "r" (&IDTPointer));
    // LoadNewIDT(&IDTPointer);
}