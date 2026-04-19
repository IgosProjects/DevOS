/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

/*
	This is the memory allocator, it handles allocating memory for the kernel.
	We currently only have a simple bump allocator, no fancy stuff yet!
*/

#include <stdint.h>
#include <stddef.h>
#include <kernel/mem.h>
#include <kernel/panic.h>

const uint32_t HeapStart = 0x01000000; // Right above 1MB(where we are loaded)
const uintptr_t HeapEnd = 0x02000000; // Where the memory heap should end(no allocations can be made)
uintptr_t NextFree = HeapStart; // Pointer to next free memory

// Allocates a certain amount of bytes, and returns the pointer to the start
// NOTE: The user must not write more than the specified amount of bytes
void* kmalloc(size_t bytes) {

	// If bigger than heap, return NULL
	if (bytes > HeapEnd - NextFree) {
		return NULL;
	}

	void* PointerToMemory = (void*)NextFree;
	NextFree += bytes; // Move the next free up

	return PointerToMemory;
}