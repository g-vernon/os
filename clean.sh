#!/bin/bash

source ./config.sh

for PROJECT in $PROJECTS; do
	(cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf os.iso
