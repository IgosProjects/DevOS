/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file holds stuff defined in "cpu.asm"

#pragma once

#include <stdint.h>

// Halt the CPU forever
extern void Halt();

// Load a new IDT(Interrupt Descriptor Table) using "lidt"
extern void LoadNewIDT(uint32_t IDTPointer);

// Generic handler to be used for ISR testing
extern void GenericISRHandler();