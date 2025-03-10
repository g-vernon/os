#!/bin/bash
IMAGE=os.iso
QEMU=qemu-system-i386

if ! $QEMU --version > /dev/null; then
	echo "$QEMU not found"
	exit 1;
fi

if ! [ -f $IMAGE ]; then
	echo "$IMAGE not found"
	exit 1;
fi

if ! $QEMU -cdrom $IMAGE; then
	echo "$QEMU exited with $?"
	exit 1;
fi
