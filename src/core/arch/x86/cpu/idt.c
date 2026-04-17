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
#include <drivers/cpu/cpu.asm.h>

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

// The IDT table holds 256 entries
IDTEntry IDTTable[256];
IDTPtr IDTTablePointer;

void UpdateTablePointer() {
    IDTTablePointer.limit = sizeof(IDTEntry) * 256 - 1; // Set the limit(size of IDT table - 1)
    IDTTablePointer.base = (uint32_t)&IDTTable[0]; // Address of first entry
}

void EditIDTEntry(int index, uint32_t handler) {
    IDTTable[index].offset_high = High16(handler);
    IDTTable[index].selector = 0x08; // Kernel code selector in GDT
    IDTTable[index].type_attr = 0x8E; // Generic flags
    IDTTable[index].zero = 0; // Allways meant to be zero
    IDTTable[index].offset_low = Low16(handler);
}

// Initilizes the IDT subsystem 
void InitIDT() {
    UpdateTablePointer();
    
    EditIDTEntry(0, (uint32_t)isr0);
    EditIDTEntry(1, (uint32_t)isr1);
    EditIDTEntry(2, (uint32_t)isr2);
    EditIDTEntry(3, (uint32_t)isr3);
    EditIDTEntry(4, (uint32_t)isr4);
    EditIDTEntry(5, (uint32_t)isr5);
    EditIDTEntry(6, (uint32_t)isr6);
    EditIDTEntry(7, (uint32_t)isr7);
    EditIDTEntry(8, (uint32_t)isr8);
    EditIDTEntry(9, (uint32_t)isr9);
    EditIDTEntry(10, (uint32_t)isr10);
    EditIDTEntry(11, (uint32_t)isr11);
    EditIDTEntry(12, (uint32_t)isr12);
    EditIDTEntry(13, (uint32_t)isr13);
    EditIDTEntry(14, (uint32_t)isr14);
    EditIDTEntry(15, (uint32_t)isr15);
    EditIDTEntry(16, (uint32_t)isr16);
    EditIDTEntry(17, (uint32_t)isr17);
    EditIDTEntry(18, (uint32_t)isr18);
    EditIDTEntry(19, (uint32_t)isr19);
    EditIDTEntry(20, (uint32_t)isr20);
    EditIDTEntry(21, (uint32_t)isr21);
    EditIDTEntry(22, (uint32_t)isr22);
    EditIDTEntry(23, (uint32_t)isr23);
    EditIDTEntry(24, (uint32_t)isr24);
    EditIDTEntry(25, (uint32_t)isr25);
    EditIDTEntry(26, (uint32_t)isr26);
    EditIDTEntry(27, (uint32_t)isr27);
    EditIDTEntry(28, (uint32_t)isr28);
    EditIDTEntry(29, (uint32_t)isr29);
    EditIDTEntry(30, (uint32_t)isr30);
    EditIDTEntry(31, (uint32_t)isr31);

    // Now set the IRQs
    EditIDTEntry(32, (uint32_t)irq0);
    EditIDTEntry(33, (uint32_t)irq1);
    EditIDTEntry(34, (uint32_t)irq2);
    EditIDTEntry(35, (uint32_t)irq3);
    EditIDTEntry(36, (uint32_t)irq4);
    EditIDTEntry(37, (uint32_t)irq5);
    EditIDTEntry(38, (uint32_t)irq6);
    EditIDTEntry(39, (uint32_t)irq7);
    EditIDTEntry(40, (uint32_t)irq8);
    EditIDTEntry(41, (uint32_t)irq9);
    EditIDTEntry(42, (uint32_t)irq10);
    EditIDTEntry(43, (uint32_t)irq11);
    EditIDTEntry(44, (uint32_t)irq12);
    EditIDTEntry(45, (uint32_t)irq13);
    EditIDTEntry(46, (uint32_t)irq14);
    EditIDTEntry(47, (uint32_t)irq15);
}

// Loads a new IDT
void LoadIDT() {
    UpdateTablePointer(); // Update so size can be recalculated

    //LoadNewIDT((uint32_t)&IDTTablePointer);
    asm volatile("lidt (%0)" : : "r" (&IDTTablePointer));
}