/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file defines PIC functions and utilities

// Remap the PIC
// REQUIRED!! Needed or else IRQs will overlap with CPU exceptions
void RemapPIC();