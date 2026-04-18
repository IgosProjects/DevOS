## Getting the tools

To build DevOS you will need some tools, i will use Linuxbrew in this tutorial!

First we need NASM to assemble the assembly code, that can be installed by doing: ```$ brew install nasm```

Then we need our compiler and linker(this will take a bit to install), so we can run the command: ```$ brew install i686-elf-gcc```

Now we need our build system, it is called GNU Make. To install it run: ```$ brew install make```

After that we need our bootloader, it is called GRUB. To install GRUB run: ```$ brew install i686-elf-grub```

Also we need QEMU, it is a x86 CPU emulator. We will use it run our OS, to install it run: ```$ brew install qemu```

Now we have all the tools! Lets get to building.

## Building DevOS

Once you have cloned the repo and have all the files you can run the ```$ make``` command to build the OS.
It will then give you an ISO file, we can run that ISO file by running the command: ```$ qemu-system-i386 -cdrom DevOS.iso```. That will open a QEMU window with GRUB the bootloader in it.
(QEMU window with GRUB in it)[assets/grub-1.png]

It will actually autoboot in 1 second by defualt, if it doenst press the enter key, then you should see the shell. Now you have built DevOS! Congrats!