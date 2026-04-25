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
#include <kernel/util/multiboot2.h>
#include <kernel/util.h>
#include <kernel/multiboot.h>

#include <drivers/display/fb.h>
#include <drivers/cpu/cpu.asm.h>
#include <drivers/vga.h>
#include <drivers/cpu/interrupts.h>
#include <drivers/audio/pcspeaker.h>
#include <drivers/debug/serial.h>

framebuffer_t Framebuffer;

char* BootBanner = "DevTerminal 1.0\nCopyright(c) 2026 EyeDev\n";

void RunTests() {

    // Test the memory allocation
    PrintString("Testing kmalloc!\n");
    void* AllocatedSpace = kmalloc(1024); // Allocate a KB of memory
    if (AllocatedSpace != NULL) {
        PrintString("OK!\n");
    } else {
        KernelPanic("Failed to allocate memory");
    }
}

// This is the kernel entry function
void StartKernel(uint32_t magic, uint32_t addr) {
    // Inside of it is where our boot file(boot.asm) calls C
    // Now that we have C we can do many thing we chouldnt before!!

    // Do multiboot2 checks

    // Check if valid and compliant bootloader
    if (magic != 0x36D76289) {
        // Do we have a multiboot compliant bootloader? If not, call a panic
        KernelPanic("Non multiboot2 compliant bootloader detected!");
    }

    // Check if MBI is aligned
    if (addr & 7) {
        // If not, kernel panic
        KernelPanic("MBI not aligned");
    }

    ParseMultibootInfo(addr, &Framebuffer); // Pass address and framebuffer

    // Initilize all systems
    InitInterrupts();
    InitSerial();
    InitFB(&Framebuffer);

    // Run kernel tests
    RunTests();

    // Beep on boot
    Beep();
    
    PrintString(BootBanner);
    PrintString("\n>");

    while (1) {
        asm volatile("hlt");
    }
}

void ExecuteCommand(char* Command) {
    if (CompareString(Command, "HI") == 0) {
        PrintString("\nHi!");
    } else if (CompareString(Command, "EXIT") == 0) {
        PrintString("\nStopping the CPU, BYE!");
        Halt(); // Halt the CPU
    } else if (CompareString(Command, "CLEAR") == 0) {
        ClearScreen(); // Clear the screen
    } else if (CompareString(Command, "MBINFO") == 0) {
        PrintString("\nMultiboot info: \n");
        char** TagArray = GetMultibootTags();
        int i = 0; // Store index 
        while (CompareString(TagArray[i], "T~") != 0) {
            PrintString(TagArray[i]); // Loop thru all tags and print the tag
            i++;
        }
    } else if (CompareString(Command, "HELP") == 0) {
        PrintString("\nHelp menu:");
        PrintString("\n    EXIT: Stops the CPU");
        PrintString("\n    HI: Prints Hi!");
        PrintString("\n    VER: Prints OS info");
        PrintString("\n    MBINFO: Shows multiboot info");
        PrintString("\n    CLEAR: Clears the screen");
    } else if (CompareString(Command, "VER") == 0) {
        PrintCharacter('\n'); // Print a newline
        PrintString("DevOS "  DEVOS_VER);
        PrintCharacter('\n'); // Print a newline
        PrintString("Build date: "  DEVOS_BUILDTIME);
    } else if (CompareString(Command, "PANIC") == 0) {
        KernelPanic("User initiated panic");
    } else if (CompareString(Command, "GARBLE") == 0) {
        while (1) {
            FBClearScreenToColor(GetRandomNumber(), GetRandomNumber(), GetRandomNumber());
        }
    } else if (CompareString(Command, "DIVIDEBYZERO") == 0) {
        int x = 0;
        int y = 15;
        int z = y / x;
    } else {
        PrintString("Invalid command!\n");
    }

    PrintString("\n>");
}
