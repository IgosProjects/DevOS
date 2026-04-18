/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/


// Halt the CPU for a certain amount of ticks
void delay(int ticks) {
    for(volatile int i = 0; i < ticks * 100000; i++);
}