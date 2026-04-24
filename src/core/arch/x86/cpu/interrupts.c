/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file handles the C side of interrupts

#include <drivers/cpu/cpu.asm.h>
#include <drivers/cpu/pic.h>
#include <drivers/cpu/interrupts.h>
#include <drivers/cpu/idt.h>
#include <drivers/vga.h>
#include <drivers/input/keyboard.h>

#include <assembly/ports.h>
#include <kernel/panic.h>
#include <kernel/devos.h>

void ISRHandler(uint32_t int_no, uint32_t err_code) {
    // Since CPU exceptions are critical, we kernel panic
    KernelPanic("what the fuck, oh yeah sorry old logic didnt work");
}

void IRQHandler(uint32_t int_no, uint32_t err_code) {
    // Print the IRQ

    // Keyboard interrupt
    if (int_no == 33) {
        OnKeyPress(int_no);
    }

    // If the interrupt came from the slave PIC
    if (int_no >= 40) {
        outb(0xA0, 0x20);
    }

    // Always send EOI to master PIC
    outb(0x20, 0x20);
}

void InitInterrupts() {
    InitIDT();
    RemapPIC();
    LoadIDT();
    asm volatile("sti"); // Turn on interrupts
}