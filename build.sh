#!/bin/bash

ASSEMBLER=i686-elf-as
C_COMPILER=i686-elf-gcc
K_BIN=os.bin
ISO_OUT=os.iso

if ! $ASSEMBLER --version > /dev/null; then
	echo "$ASSEMBLER" not found.
	exit 1
elif ! $C_COMPILER --version > /dev/null; then
	echo "$C_COMPILER" not found.
	exit 1
fi

if ! grub-mkrescue --version > /dev/null; then
	echo "grub-mkrescue not found."
	exit 1
fi

# Build boot assembly script -- this sets up a stack for C to use
if ! i686-elf-as boot.s -o boot.o; then
	echo "Assembler failed with $?"
	exit 1
fi

# Build kernel main
if ! i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra; then
	echo "Compiler failed with $?"
	exit 1
fi

# Link kernel
if ! i686-elf-gcc -T linker.ld -o $K_BIN -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc; then
	echo "Linker failed with $?"
	exit 1
fi

# Make ISO image
rm -r isodir
mkdir -p isodir/boot/grub
cp $K_BIN isodir/boot/$K_BIN
cp grub.cfg isodir/boot/grub/grub.cfg
if ! grub-mkrescue -o $ISO_OUT isodir; then
	echo "grub-mkrescue failed with $?"
	echo "Failed to make ISO"
	exit 1
else
	echo "OS built succesfully. ISO produced in $ISO_OUT"	
	exit 0
fi
