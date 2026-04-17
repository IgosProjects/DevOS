/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file defines functions in "idt.c"

#pragma once

#include <stdint.h>

// Setup the IDT for use
void InitIDT();

// Change a entry in the IDT table
void SetIDTEntry(int index, uint32_t handler);

// Load the current IDT
void LoadIDT();