/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

#include <kernel/util/multiboot2.h>
#include <drivers/vga.h>
#include <stdint.h>

char* TagArray[512]; // Create an array to store the tags
uint32_t TagArrayIndex = 0; 

// Parses the multiboot info, and handles the values
void ParseMultibootInfo(unsigned long addr) {
	uint8_t* pointer = (uint8_t*)addr + 8; // Pointer after 8 bytes of Multiboot addr

	// Loop thru all tags
    while (1) {
        struct multiboot_tag* tag = (struct multiboot_tag*)pointer;

        if (tag->type == MULTIBOOT_TAG_TYPE_MODULE) {
        	PrintString("Found multiboot2 module!");
            TagArray[TagArrayIndex++] = "MODULE\n"; // Append to tag list
        } else if (tag->type == MULTIBOOT_TAG_TYPE_MMAP) {
            TagArray[TagArrayIndex++] = "MEMORY MAP\n"; 
        } else if (tag->type == MULTIBOOT_TAG_TYPE_CMDLINE) {
            TagArray[TagArrayIndex++] = "COMMAND LINE\n";
        } else if (tag->type == MULTIBOOT_TAG_TYPE_BASIC_MEMINFO) {
            TagArray[TagArrayIndex++] = "BASIC MEMINFO\n";
        } else if (tag->type == MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME) {
            TagArray[TagArrayIndex++] = "BOOTLOADER NAME\n";
        } else if (tag->type == MULTIBOOT_TAG_TYPE_END) {
            TagArray[TagArrayIndex++] = "END\n";
            TagArray[TagArrayIndex] = "T~"; // Append terminator
            break;
        } else {
            TagArray[TagArrayIndex++] = "UNKNOWN\n";
        }

        // Move to next tag (aligned to 8 bytes)
        pointer += (tag->size + 7) & ~7;
    }
}

// Returns an array of tags
char** GetMultibootTags() {
    return TagArray;
}