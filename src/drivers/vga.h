#ifndef VGA_H
#define VGA_H

void new_line();
int is_offscreen();
void vga_disable_cursor();
void vga_putchar(char c);
void vga_print(char *text);

#endif
