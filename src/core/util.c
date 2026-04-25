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

static uint32_t seed = 123456789; // Seed used for random function

// Halt the CPU for a certain amount of ticks
void delay(int ticks) {
    for(volatile int i = 0; i < ticks * 100000; i++);
}

// Compares two strings
int CompareString(const char *s1, const char *s2) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = s1[i];
        char c2 = s2[i];

        // Convert to lowercase
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

        if (c1 != c2)
            return (unsigned char)c1 - (unsigned char)c2;

        i++;
    }

    // Handle end of string
    char c1 = s1[i];
    char c2 = s2[i];

    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;

    return (unsigned char)c1 - (unsigned char)c2;
}

// Returns a random number, using the seed stored in kernel
uint32_t GetRandomNumber() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}