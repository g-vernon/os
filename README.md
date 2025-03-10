# OS

## Description

This repo controls my toy OS being developed using material from wiki.osdev.org. It targets i686 and is being tested against the QEMU hardware emulator.

## Building

A cross-compilation toolchain must be configured as per <https://wiki.osdev.org/GCC_Cross-Compiler>

It should be placed on the user path so that the programs `i686-elf-as` and `i686-elf-gcc` are available.

Then run `build.sh`

## Emulation

Install qemu-full e.g. `pacman -Syu qemu-full`

Then run `qemu-system-i386 -cdrom os.iso`

On success a GRUB menu will be seen and the OS will boot to a "Hello kernel-space" dialog.
