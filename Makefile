CC := i686-elf-gcc
AS := i686-elf-as
OBJ_FILES := boot.o kernel.o
K_BIN := os.bin
ISO := os.iso
ISODIR := isodir
LINKER_SCRIPT := linker.ld
CFLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKER_FLAGS := -ffreestanding -O2 -nostdlib -lgcc

all: $(ISO)
	$(RM) -r $(ISODIR)
	mkdir -p $(ISODIR)/boot/grub
	cp $(K_BIN) $(ISODIR)/boot/$(K_BIN)
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) isodir

$(ISO): $(K_BIN)

$(K_BIN): $(OBJ_FILES)
	$(CC) -T $(LINKER_SCRIPT) -o $(K_BIN) $(LINKER_FLAGS) $(OBJ_FILES)

boot.o: boot.s
	$(AS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)

clean:
	$(RM) $(wildcard $(OBJ_FILES) $(K_BIN) $(ISO))
