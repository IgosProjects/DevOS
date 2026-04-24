/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

// This is the keyboard driver, we only support PS/2 for now, USB is not implemented!
// NOTE: Some newer computers dont emulate PS/2 for USB keyboards!

#include <assembly/ports.h>
#include <drivers/vga.h>
#include <drivers/display/fb.h>
#include <kernel/devos.h>

#include <stdint.h>
#include <stdbool.h>

#define CAPSLOCK 0x3A // Capslock keycode
#define SHIFT_DOWN 0x2A // Shift down keycode
#define SHIFT_UP 0xAA // Shift up keycode
#define ENTER 0x1C // Enter keycode
#define BACKSPACE 0x0E // Backspace keycode

// All the scancodes in QWERTY keyboard defined(uppercase)
const char ScancodeASCIIUppercase[] = {'?', '?', '!', '"', '#', '$', '%', '&',
                         '/', '(', ')', '=', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
                         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
                         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
                         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

// All the scancodes in QWERTY keyboard defined(lowercase)
const char ScancodeASCIILowercase[] = {'?', '?', '1', '2', '3', '4', '5', '6',
                         '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
                         'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
                         'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
                         'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

bool Capslock = false;

// COMMAND LINE
char CommandBuffer[256];
int BufferIndex = 0;

void ClearCommandBuffer() {
	for (int i = 0; i < 512; i++) {
    	CommandBuffer[i] = 0;
	}
}

void OnKeyPress(uint32_t int_no) {
	uint8_t Scancode = inb(0x60); // Read scancode from port

	// Toggle capslock
	if (Scancode == CAPSLOCK) {
		if (Capslock == false) {
			Capslock = true;
		} else {
			Capslock = false;
		}

		return;
	}

	if (Scancode == SHIFT_DOWN) {
		Capslock = true; // If shift is down, enable capslock
		return;
	} else if (Scancode == SHIFT_UP) {
		Capslock = false; // Disable when raised
		return;
	}

	if (Scancode == BACKSPACE) {
		if (BufferIndex <= 0) return;

		CommandBuffer[BufferIndex - 1] = ' '; // Set to space
		FBPrintBackspace();

		BufferIndex -= 1;

		return;
	}

	if (Scancode == ENTER) {
		// When enter is pressed we need to execute the command
		CommandBuffer[BufferIndex + 1] = '\0'; // Add null terminator
		ExecuteCommand(CommandBuffer);

		ClearCommandBuffer();
		return;
	}

	char Character; // Predefine to fix GCC errors

	// If shiftlock is off use lowercase
	if (!Capslock) {
		Character = ScancodeASCIILowercase[(int) Scancode]; // Convert to ASCII
	} else {
		// If shiftlock is on use uppercase
		Character = ScancodeASCIIUppercase[(int) Scancode]; // Convert to ASCII
	}


	if ((Scancode & 0x80) == 0) {
		PrintCharacter(Character); // Print it
		CommandBuffer[BufferIndex] = Character; // Add character 
		BufferIndex++;
	}
}

void InitKeyboard() {

}