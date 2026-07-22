#include "vga.h"

static char *video = (char *)0xB8000;

static int cursor_x = 0;
static int cursor_y = 0;

void new_line() {
	cursor_x = 0;
	cursor_y++;
}

void backspace() {
	if (cursor_x > 0) {
		cursor_x--;
	} else if (cursor_y > 0) {
		cursor_y--;
		cursor_x = 79;
	} else {
		return;
	}
	int index = cursor_y * 80 + cursor_x;
	video[index * 2] = ' ';
	video[index * 2 + 1] = 0x07;
}

int is_offscreen() {
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}
	return 0;
}

void vga_disable_cursor() {
	outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_putchar(char c) {
	if (is_offscreen()) {
		new_line();
	}
	if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
		return;
	} else if (c == ' ') {
		cursor_x++;
		return;
	} else if (c == '\b') {
		backspace();
		return;
	}
	int index = cursor_y * 80 + cursor_x;
	// 0 1 2 3
	// a c b c
	video[index * 2] = c;
	video[index * 2 + 1] = 0x07;

	cursor_x++;
}

void vga_print(char *text) {
	for (char *c = text; *c != '\0'; c++) {
		vga_putchar(*c);
	}
}
