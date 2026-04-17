/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file defines commonly used kernel functions

// Global values
#define DEVOS_BUILDTIME __DATE__
#define DEVOS_VER "1.0.2"

// Used to get the high and low addresses of a 16 bit value
#define Low16(address) (uint16_t)((address) & 0xFFFF)
#define High16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

// INLINE FUNCTIONS

// Joins 2 strings thogether and outputs into a final buffer
static inline void Join2Strings(char* str1, char* str2, char StringBuffer[]) {
    int BufferIndex = 0;

    while (*str1) {
        // Loop thru all of string one
        StringBuffer[BufferIndex] = *str1;
        str1++; // Increment pointer
        BufferIndex++; // Increment index
    }

    // Repeat for second string
    while (*str2) {
        // Loop thru all of string two
        StringBuffer[BufferIndex] = *str2;
        str2++; // Increment pointer
        BufferIndex++; // Increment index
    }

    StringBuffer[BufferIndex] = '\0'; // Add null terminator
}

void ExecuteCommand(char* Command);

#define true 1
#define false 0