#include "io.h"

void putchar(char c) {
	while (!(inb(0x3F8 + 5) & 0x20));
    outb(0x3F8, c);
}

void print(char* text) {
    for (char *c = text; *c != '\0'; c++) {
    	putchar(*c);
    }
}

char *video = (char*)0xB8000;

void print_vga(char *text) {
    int pos = 0;

    for (char *c = text; *c != '\0'; c++) {
        video[pos] = *c;
        video[pos + 1] = 0x07;

        pos += 2;
    }
}

void kernel_main() {
    //print("hello world\n");
    print_vga("hello world");
    while(1);
}
