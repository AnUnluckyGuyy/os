static char *video = (char *)0xB8000;

static int cursor_x = 0;
static int cursor_y = 0;

void new_line() {
	cursor_x = 0;
	cursor_y++;
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
	}
	int index = (cursor_y * 80 + cursor_x) * 2;

	video[index] = c;
	video[index + 1] = 0x07;

	cursor_x++;
}

void vga_print(char *text) {
	for (char *c = text; *c != '\0'; c++) {
		vga_putchar(*c);
	}
}
