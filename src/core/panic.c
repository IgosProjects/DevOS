/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file handles panicing the kernel, it is very small(not gonna be later probably)
// It prints debug info and stuff

#include <drivers/vga.h>
#include <drivers/cpu/cpu.asm.h>
#include <kernel/devos.h>

// Panic the kernel with a reason provided
void KernelPanic(const char* reason) {
    ClearScreen();

    PrintString("---------PANIC START---------\n\n");
    PrintString("DevOS has encountered a problem and was shutdown.\n");
    PrintString("Please make an issue on Github and reboot the system!!\n");
    
    PrintString("Kernel version: "  DEVOS_VER);
    PrintString("\nKernel build date: "  DEVOS_BUILDTIME);
    PrintString("\nReason: ");
    PrintString(reason);
    PrintString("\n\n----------PANIC END----------\n");
    
    // Now we need to halt the CPU(we can use the CPU driver for that)
    Halt();
}