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

typedef struct framebuffer_t {
    uint32_t SizeX;
    uint32_t SizeY;
    uint64_t Addr;
    uint32_t Pitch;

    uint8_t Type;
    uint8_t BPP;

    uint32_t RedOffset;
    uint32_t RedSize;

    uint32_t GreenOffset;
    uint32_t GreenSize;

    uint32_t BlueOffset;
    uint32_t BlueSize;

} framebuffer_t;


// Initilizes the framebuffer driver, and draws a test pixel
void InitFB(framebuffer_t* FramebufferPointer);

// Draws a pixel of any color, at any position
void DrawPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);

// Prints a single character to the framebuffer
void FBPrintChar(char c, uint32_t scale);

// Prints a string to framebuffer
void FBPrintString(const char* String);

// Clears the framebuffer screen to black
void FBClearScreen();

// Clears the framebuffer screen to a specified color
void FBClearScreenToColor(int r, int g, int b);

// Prints a hex value to the screen
void FBPrintHex(uint32_t value);

// Removes the last character, and moves back the cursor
void FBPrintBackspace();