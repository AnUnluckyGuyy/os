#ifndef VGA_H
#define VGA_H

#include "../../cpu/io.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25

void new_line();
int is_offscreen();
void vga_disable_cursor();
void vga_init();
void vga_putchar(char c);
void vga_print(char *text);

#endif
