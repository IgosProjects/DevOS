/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This is the framebuffer driver, it handles the framebuffer passed by GRUB or other bootloaders

#include <stdint.h>
#include <drivers/display/fb.h>
#include <kernel/util/font_8x8.h>

framebuffer_t* LocalFramebuffer; // NOTE: dont rename, linker will complain

uint32_t CursorX = 0;
uint32_t CursorY = 0;

void DrawPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
    uint8_t* base = (uint8_t*)(uintptr_t)LocalFramebuffer->Addr; // Get address pointer

    // Calculate where the pixel is
    uint32_t bytes_per_pixel = LocalFramebuffer->BPP / 8;
    uint32_t offset = y * LocalFramebuffer->Pitch + x * bytes_per_pixel;

    // Build the color using the provided formats
    uint32_t color =
        (r << LocalFramebuffer->RedOffset) |
        (g   << LocalFramebuffer->GreenOffset) |
        (b   << LocalFramebuffer->BlueOffset);

    // Finnaly draw the pixel
    *(uint32_t*)(base + offset) = color;
}

// Prints a single character to the framebuffer
void FBPrintChar(char c, uint32_t scale) {
    uint8_t* glyph = font8x8_basic[(uint8_t)c];
    framebuffer_t* fb = LocalFramebuffer;

    if (c == '\n') {
        CursorX = 0; // Set cursor X to 0
        CursorY += 8 * scale; // Move down by one line

        return;
    }

    for (uint32_t row = 0; row < 8; row++) {
        for (uint32_t col = 0; col < 8; col++) {

            if (glyph[row] & (1 << col)) {

                // Draw as scaled block instead
                for (uint32_t dy = 0; dy < scale; dy++) {
                    for (uint32_t dx = 0; dx < scale; dx++) {
                        DrawPixel(CursorX + col * scale + dx, CursorY + row * scale + dy, 255, 255, 255);
                    }
                }

            }

        }
    }

    CursorX += 8 * scale;
}

// Clears the framebuffer screen to blacjk
void FBClearScreen() {
    uint8_t* base = (uint8_t*)(uintptr_t)LocalFramebuffer->Addr;
    uint32_t bytes_per_pixel = LocalFramebuffer->BPP / 8;

    for (uint32_t y = 0; y < LocalFramebuffer->SizeY; y++) {
        for (uint32_t x = 0; x < LocalFramebuffer->SizeX; x++) {
            uint32_t offset = y * LocalFramebuffer->Pitch + x * bytes_per_pixel;
            *(uint32_t*)(base + offset) = 0;
        }
    }
}

// Prints a string to framebuffer
void FBPrintString(const char* String) {
    while (*String) {
        FBPrintChar(*String++, 2); // Loop until null terminate
    }
}

// Initilizes the framebuffer driver, and draws a test pixel
void InitFB(framebuffer_t* FramebufferPointer) {
    LocalFramebuffer = FramebufferPointer; // Set LocalFramebuffer
}