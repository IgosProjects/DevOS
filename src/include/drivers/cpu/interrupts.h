/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file holds function blueprints for the interrupt subsystem

#include <stdint.h>

// Registers defined as a struct
typedef struct {
    uint32_t int_no;
    uint32_t err_code;
} registers_t;

// Setup interrupts
void InitInterrupts();