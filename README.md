## DevOS

![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![GitHub Downloads (all assets, all releases)](https://img.shields.io/github/downloads/IgosProjects/DevOS/total)
![Stars](https://img.shields.io/github/stars/IgosProjects/DevOS)
![Forks](https://img.shields.io/github/forks/IgosProjects/DevOS) 

DevOS is a small educational OS, it is written in C++ and the Assembly language. DevOS is highly experminatal and doesnt have much to it!!

## How do i build it?

To build DevOS you will need a compiler for x86. One can be found or built but im for the sake of you reading, gonna use Linuxbrew(Homebrew works too)!!

If you dont have Linuxbrew installed you can go to "brew.sh" and run the command, now you have Linuxbrew but just in case run "brew" if it outputs something, you got it. Now we need to install the compiler so run "brew install x86_64-elf-gcc". And now you need one more piece called an assembler. An assembler assembles assembly files(try to use the work assemble more times than this in a single sentance). So to install that run "brew install nasm". Actually i lied we need one more thing, its called QEMU and it is a CPU emulator that we will use to run our OS. So run "brew install qemu" and now proceed to the next step.

Now we need to build the OS so run "make ISOImage" this will output an ISO into the project root. Then run "qemu-system-x86_64 -cdrom DevOS.iso" and boom it works!! You have built DevOS from scratch!🎉🎉

## Contributing
Contributing on DevOS is quite easy!! You need to make a pull request, then you have to wait for me to check it. And after that well you wait for me to accept it, and then congrats!! You contributed🎉.

But beware im busy doing school and such so i cant review all the time!!