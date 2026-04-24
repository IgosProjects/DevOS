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
// FUTURE ME: yes it does, as of 4/23/2026 it has framebuffer

#include <stdint.h>
#include <drivers/display/fb.h>

void PrintCharacter(const char Character) {
    FBPrintChar(Character, 2);
}

void ClearScreen() {
    FBClearScreen();
}

void PrintString(const char* String) {
    FBPrintString(String);
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