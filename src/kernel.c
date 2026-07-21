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

void kernel_main() {
    print("hello world\n");
    while(1);
}
