/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This is the kernel, it is the core of any OS. It runs your apps and lets you watch your videos.
// There are many critical parts to a kernel, such as:
// 1. A memory manager
// 2. A VGA driver
// 3. A filesystem
// 4. A userspace(to run user apps)

// But currently this kernel is very barebones!!

#include <drivers/vga.h>
#include <drivers/cpu/interrupts.h>

// This is the kernel entry function
void StartKernel() {
    // Inside of it is where our boot file(boot.asm) calls C
    // Now that we have C we can do many thing we chouldnt before!!

    PrintString("Hello world!!");

    InitInterrupts();
    asm volatile("sti");

    // Halt the CPU
    while (1 == 1) {
        asm volatile("hlt");
    }
}