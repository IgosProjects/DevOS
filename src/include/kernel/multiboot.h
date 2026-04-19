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

// Parses the multiboot info, and handles the values
void ParseMultibootInfo(unsigned long addr);

// Returns an array of tags
char** GetMultibootTags();