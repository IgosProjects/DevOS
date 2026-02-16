/*
 * This file is part of DevOS
 * 
 * Copyright© 2026 EyeDev
 * 
 * DevOS is free software: you can redistribute it and/or modify it under the
 * terms of the MIT License. See LICENSE for full details of all licenses
 * that apply to this repository.
*/

/* This is the linker script, it tells our linker how to link our ELF file thogether */

ENTRY(start)

SECTIONS {
    . = 1M;

    .multiboot2 ALIGN(8) : {
        /* ensure that the multiboot header is at the beginning */
        KEEP(*(.multiboot2))
    }

    .text ALIGN(16) : {
        *(.text)
    }

    /* Read writable data */
    .rodata ALIGN(16) : {
        *(.rodata)
    }

    /* Writable initialized data */
    .data ALIGN(16) : {
        *(.data)
    }

    /* Uninitialized data (zeroed at boot) */
    .bss ALIGN(16) : {
        *(COMMON)
        *(.bss)
    }
}
