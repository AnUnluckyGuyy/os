#ifndef SERIAL_H
#define SERIAL_H

#define COM1 0x3F8

void serial_putchar(char c);
void serial_print(char *text);

#endif
