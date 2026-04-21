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
#define COM1 0x3F8 // COM1 is located at this port

// Initilizes the serial driver, allows for debugging
void InitSerial();

// Writes a single character to serial COM1
void WriteSerialChar(char Character);