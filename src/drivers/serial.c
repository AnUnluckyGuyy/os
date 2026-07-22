#include "serial.h"
#include "../cpu/io.h"

void serial_putchar(char c)
{
    while (!(inb(COM1 + 5) & 0x20));

    outb(COM1, c);
}

void serial_print(char *text) {
	for (char *c = text; *c != '\0'; c++) {
		serial_putchar(*c);
	}
}
