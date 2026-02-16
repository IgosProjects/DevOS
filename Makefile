# * This file is part of DevOS
# * 
# * Copyright© 2026 EyeDev
# * 
# * DevOS is free software: you can redistribute it and/or modify it under the
# * terms of the MIT License. See LICENSE for full details of all licenses
# * that apply to this repository.

# Compiler used to build configuration and other tools
HOSTCC = cc

include build.cfg # Include the configuration file

# Get all the sources
CPPSOURCES = $(wildcard src/core/*.cpp)
ASMSOURCES = $(wildcard src/boot/*.asm)

# Convert it into objects
CPPOBJS = $(CPPSOURCES:.cpp=.cpp.o)
ASMOBJS = $(ASMSOURCES:.asm=.asm.o)

all: $(ISO)

# Rule to compile ASM files
%.asm.o: %.asm
	@echo "AS		$<"
	@$(KERNELAS) $(ASFLAGS) $< -o $@

%.cpp.o: %.cpp
	@echo "CXX		$<"
	@$(KERNELCXX) $(CFLAGS) -c $< -o $@

# Link into an ELF
$(ELF): $(CPPOBJS) $(ASMOBJS)
	$(KERNELLD) $(LDFLAGS) $^ -o $@

$(ISO): $(ELF)
	mkdir -p build/iso/boot/grub
	cp grub.cfg build/iso/boot/grub
	cp $(ELF) build/iso/boot
	grub-mkrescue build/iso -o $(ISO)