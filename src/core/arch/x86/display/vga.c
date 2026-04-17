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
#include <assembly/ports.h>

uint8_t CursorX = 0;
uint8_t CursorY = 0;

// Place in memory where VGA is stored
volatile uint16_t* VGABuffer = (volatile uint16_t*)0xB8000;
uint8_t CurrentVGAColor = 0x0F; 

uint16_t VGAWidth  = 80;
uint16_t VGAHeight = 25;

// Move the cursor to a certain X and Y value
void UpdateVGACursor(int x, int y) {
	uint16_t position = y * VGAWidth + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (position & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((position >> 8) & 0xFF));
}

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

void ClearScreen() {
    int counter1 = 0;
    int counter2 = 0;

    // Loop thru each coloum
    while (!counter1 == VGAHeight) {
        // Loop thru each characther
        while (!counter2 == VGAWidth) {
            PrintCharacter('H');
        }
    }

    // Now we reset the cursor(to prevent writing off screen)
    CursorX = 0;
    CursorY = 0;
    UpdateVGACursor(0, 0);
}

void PrintString(const char* String) {
    while (*String) {
        PrintCharacter(*String++); // Loop until null terminate
    }

    // Update the cursor
    UpdateVGACursor(CursorX, CursorY);
}

char* NumToString(uint32_t number, char Buffer[]) {
    int i = 10; // index
    Buffer[i] = '\0';
    if (number == 0) {
        Buffer[--i] = '0';
    } else {
        while(number > 0) {
            Buffer[--i] = '0' + (number % 10);
            number /= 10;
        }
    }
    
    return Buffer;
}

void PrintNumber(uint32_t number) {
    char OutputBuffer[100];
    NumToString(number, OutputBuffer);
    PrintString(OutputBuffer);
}