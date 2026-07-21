CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -nostdlib -c
LDFLAGS = -m elf_i386 -T linker.ld

SRC = src
BUILD = build
ISO = iso

all: os.iso

$(BUILD)/boot.o: $(SRC)/boot.asm
	mkdir -p $(BUILD)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel.o: $(SRC)/kernel.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/kernel.bin: $(BUILD)/boot.o $(BUILD)/kernel.o
	$(LD) $(LDFLAGS) -o $@ $^

$(ISO)/boot/kernel.bin: $(BUILD)/kernel.bin
	mkdir -p $(ISO)/boot
	cp $< $@

os.iso: $(ISO)/boot/kernel.bin
	grub-mkrescue -o $@ $(ISO)

run: os.iso
	qemu-system-i386 -cdrom os.iso -nographic

clean:
	rm -rf $(BUILD)
	rm -f os.iso