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

// VGA driver class
class VGA {
    private:
 
    public:
        static void PrintCharacter(const char Character);
        static void PrintString(const char* String);
};