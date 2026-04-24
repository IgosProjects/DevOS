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
#include <drivers/display/fb.h>
#include <drivers/cpu/cpu.asm.h>
#include <kernel/devos.h>

void PrintStackTrace(uint32_t* ebp) {
    FBPrintString("\n--- STACK TRACE ---\n\n");

    for (int i = 0; i < 10; i++) {
        if (!ebp) break;

        uint32_t ret = *(ebp + 1); // Return address

        FBPrintString("  ");
        FBPrintHex(ret);
        FBPrintString("\n");

        ebp = (uint32_t*)(*ebp); // Previus frame
    }

    FBPrintString("\n---- END TRACE ----\n\n");
}

// Panic the kernel with a reason provided
void KernelPanic(const char* reason) {
    FBClearScreenToColor(255, 0, 0); // Fill the screen with red

    PrintString("---------PANIC START---------\n\n");
    PrintString("DevOS has encountered a problem and was shutdown.\n");
    PrintString("Please make an issue on Github and reboot the system!!\n");

    uint32_t ebp;
    __asm__ volatile ("mov %%ebp, %0" : "=r"(ebp));

    PrintStackTrace((uint32_t*)ebp);

    PrintString("Kernel version: "  DEVOS_VER);
    PrintString("\nKernel build date: "  DEVOS_BUILDTIME);
    PrintString("\nReason: ");
    PrintString(reason);
    PrintString("\n\n----------PANIC END----------\n");
    
    // Now we need to halt the CPU(we can use the CPU driver for that)
    Halt();
}