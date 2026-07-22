CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -fno-pie -nostdlib -c
LDFLAGS = -m elf_i386 -T linker.ld

SRC = src
BUILD = build
ISO = iso

all: os.iso

$(BUILD)/boot.o: $(SRC)/boot/boot.asm
	mkdir -p $(BUILD)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel.o: $(SRC)/kernel/kernel.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/vga.o: $(SRC)/drivers/vga.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/serial.o: $(SRC)/drivers/serial.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/keyboard.o: $(SRC)/drivers/keyboard.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/io.o: $(SRC)/cpu/io.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD)/kernel.bin: $(BUILD)/boot.o $(BUILD)/kernel.o $(BUILD)/vga.o $(BUILD)/serial.o $(BUILD)/keyboard.o $(BUILD)/io.o
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
