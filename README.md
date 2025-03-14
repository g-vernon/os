# OS

## Description

This repo controls my toy OS being developed using material from wiki.osdev.org. It targets i686 and is being tested against the QEMU hardware emulator.

## Build prerequisites

A cross-compilation toolchain must be configured as per <https://wiki.osdev.org/GCC_Cross-Compiler>

It should be placed on the user path so that the programs `i686-elf-as` and `i686-elf-gcc` are available.

## Build

Ensure build prerequisites are met.

Run `./iso.sh`

This will produce an ISO image `os.iso`

## Emulation

Install qemu-full e.g. `pacman -Syu qemu-full`

Run `./run_emulator.sh`

This will invoke `qemu-system-i386 -cdrom os.iso`

On success a GRUB menu will be seen and the OS will boot to a "Hello kernel-space" dialog.
