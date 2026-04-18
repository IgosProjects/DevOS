/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/


#include <assembly/ports.h>
#include <kernel/util.h>
#include <stdint.h>

int Song[] = {
    659, 659, 0, 659, 0, 523, 659, 0,
    784, 0, 0, 0,
    392
};

int SongLenght = sizeof(Song) / sizeof(Song[0]);

// Play a beep on a specific frequency
void PlaySound(uint32_t nFrequence) {
	uint32_t Div;
	uint8_t tmp;
 
	// Set the PIT to the desired frequency
	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t) (Div) );
	outb(0x42, (uint8_t) (Div >> 8));
 
	// And now finnaly play the sound
	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}
 
// Stop the sound
void StopSound() {
	uint8_t tmp = inb(0x61) & 0xFC;
     
	outb(0x61, tmp);
}

#define NOTE_DELAY 2000 // Delay in ms
 
void PlaySong() {
    for (int i = 0; i < SongLenght; i++) {
        int freq = Song[i];

        if (freq == 0) {
            StopSound();   // silence
        } else {
            PlaySound(freq); // set PIT + enable speaker
        }

        delay(NOTE_DELAY);
    }

    StopSound();
}

// Make a beep
void Beep() {
	PlaySound(1000);
	delay(10);
	StopSound();
}