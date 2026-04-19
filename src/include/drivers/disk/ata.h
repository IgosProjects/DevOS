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

// Read a sector from the master ATA drive
void ReadSectorATA(uint32_t sector, uint16_t* buffer);