/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file defines commonly used kernel functions

// Used to get the high and low addresses of a 16 bit value
#define Low16(address) (uint16_t)((address) & 0xFFFF)
#define High16(address) (uint16_t)(((address) >> 16) & 0xFFFF)