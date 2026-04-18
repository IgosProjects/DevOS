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

#include <kernel/devos.h>
#include <kernel/panic.h>
#include <kernel/mem.h>

#include <drivers/cpu/cpu.asm.h>
#include <drivers/vga.h>
#include <drivers/cpu/interrupts.h>
#include <drivers/printf/tinyprintf.h>
#include <drivers/audio/pcspeaker.h>

void RunTests() {

    // Test the memory allocation
    PrintString("Testing kmalloc!\n");
    void* AllocatedSpace = kmalloc(1048576); // Allocate a MB of memory
    if (AllocatedSpace) {
        PrintString("OK!\n");
    } else {
        KernelPanic("Failed to allocate memory");
    }
}

// This is the kernel entry function
void StartKernel() {
    // Inside of it is where our boot file(boot.asm) calls C
    // Now that we have C we can do many thing we chouldnt before!!

    // Initilize all systems
    InitInterrupts();

    // Run kernel tests
    RunTests();

    // Beep on boot
    Beep();

    PrintString("\n>");

    while (1) {
        asm volatile("hlt");
    }
}

int CompareString(const char *s1, const char *s2) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = s1[i];
        char c2 = s2[i];

        // Convert to lowercase
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 != c2)
            return (unsigned char)c1 - (unsigned char)c2;

        i++;
    }

    // Handle end of string
    char c1 = s1[i];
    char c2 = s2[i];

    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

    return (unsigned char)c1 - (unsigned char)c2;
}

void ExecuteCommand(char* Command) {
    if (CompareString(Command, "HI") == 0) {
        PrintString("\nHi!");
    } else if (CompareString(Command, "EXIT") == 0) {
        PrintString("\nStopping the CPU, BYE!");
        Halt(); // Halt the CPU
    } else if (CompareString(Command, "HELP") == 0) {
        PrintString("\nHelp menu:");
        PrintString("\n    EXIT: Stops the CPU");
        PrintString("\n    HI: Prints Hi!");
    } else {
        PrintString("Invalid command!\n");
    }

    PrintString("\n>");
}
