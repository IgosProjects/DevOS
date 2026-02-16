/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

#include <stdint.h>

uint8_t CursorX = 0;
uint8_t CursorY = 0;

// Place in memory where VGA is stored
uint16_t VGABuffer = (volatile uint16_t*)0xB8000;

// VGA driver class
class VGA {
    private:

    public:
        static void PrintCharacter(char Character);
};

// Prints a single character to the screen
void VGA::PrintCharacter(char Character) {

}
