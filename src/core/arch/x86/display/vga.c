/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This is the VGA driver, it lets you display stuff on the screen!! It is very simple and doesnt implement anything other than VGA text mode

#include <stdint.h>
#include <drivers/vga.h>

uint8_t CursorX = 0;
uint8_t CursorY = 0;

// Place in memory where VGA is stored
volatile uint16_t* VGABuffer = (volatile uint16_t*)0xB8000;
uint8_t CurrentVGAColor = 0x0F; 

uint16_t VGAWidth  = 80;
uint16_t VGAHeight = 25;

// Prints a single character to the screen
void PrintCharacter(const char Character) {
    if (Character == '\n') {
        CursorX = 0;
        CursorY++; // Move down a line

        return; // FIX: Return instead of printing the symbol
    };

    VGABuffer[CursorY * VGAWidth + CursorX] = (CurrentVGAColor << 8) | Character;
    CursorX++; // Move one row forward
}

void PrintString(const char* String) {
    while (*String) {
        PrintCharacter(*String++); // Loop until null terminate
    }
}