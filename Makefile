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
CSOURCES = $(wildcard src/core/*.c src/core/arch/$(TARGETARCH)/*/*.c src/drivers/*/*.c) # Driver files are all 2 directories deep
ASMSOURCES = $(wildcard src/boot/*.asm src/core/arch/$(TARGETARCH)/*/*.asm src/drivers/*/*.asm)

# Convert it into objects
COBJS = $(CSOURCES:.c=.c.o)
ASMOBJS = $(ASMSOURCES:.asm=.asm.o)

all: $(ISO)

# Rule to compile ASM files
%.asm.o: %.asm
	@echo "AS		$<"
	@$(KERNELAS) $(ASFLAGS) $< -o $@

%.c.o: %.c
	@echo "CC		$<"
	@$(KERNELCC) $(CFLAGS) -c $< -o $@

# Link into an ELF
$(ELF): $(COBJS) $(ASMOBJS)
	@echo "LD		$@"
	@$(KERNELLD) $(LDFLAGS) $(COBJS) $(ASMOBJS) -o $@

# Create an ISO
$(ISO): $(ELF)
	@mkdir -p build/iso/boot/grub
	@cp grub.cfg build/iso/boot/grub
	@cp $(ELF) build/iso/boot
	@grub-mkrescue build/iso -o $(ISO)

clean:
	@rm -rf $(COBJS) $(ASMOBJS) $(ISO) $(ELF)