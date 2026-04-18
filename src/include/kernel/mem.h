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
#include <stddef.h>
#include <stdint.h>

// Allocates a certain amount of bytes, and returns the pointer to the start
// NOTE: The user must not write more than the specified amount of bytes
void* kmalloc(size_t bytes);