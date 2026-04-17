/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

#pragma once

#include <stdint.h>

// Print a single characther to the screen
void PrintCharacter(const char Character);

// Print a (null terminated)string to the screen
void PrintString(const char* String);

// Print a 32 bit integer to the screen
void PrintNumber(uint32_t number);

// Clear the screen
void ClearScreen();

// Converts a number to a string and returns it
char* NumToString(uint32_t number, char Buffer[]);