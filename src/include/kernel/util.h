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

// Halt the CPU for a certain amount of ticks
void delay(int ticks);

// Compares two strings
int CompareString(const char *s1, const char *s2);

// Returns a random number, using the seed stored in kernel
uint32_t GetRandomNumber();