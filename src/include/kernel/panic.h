/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This file defines the kernel panic function that can be found in "panic.c"

#pragma once

// Trigger a kernel panic with a specified reason
void KernelPanic(const char* reason);