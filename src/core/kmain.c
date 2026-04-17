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
#include <drivers/cpu/cpu.asm.h>

#include <drivers/vga.h>
#include <drivers/cpu/interrupts.h>
#include <drivers/printf/tinyprintf.h>

// This is the kernel entry function
void StartKernel() {
    // Inside of it is where our boot file(boot.asm) calls C
    // Now that we have C we can do many thing we chouldnt before!!


    // Initilize all systems
    init_printf(PrintCharacter, 0);
    InitInterrupts();

    int counter = 0;
    int counter2 = 0;

    // TODO: Add shell
    PrintString("\n>");

    while (1) {
        asm volatile("hlt");
    }
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int CompareString(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void ExecuteCommand(char* Command) {
    if (CompareString(Command, "HI") == 0) {
        PrintString("Hi!\n");
    } else {
        PrintString("Invalid command!\n");
        PrintString(">");
    }
}
