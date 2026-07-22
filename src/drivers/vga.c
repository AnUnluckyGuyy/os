static char *video = (char *)0xB8000;

static int cursor_x = 0;
static int cursor_y = 0;

void vga_putchar(char c) {
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
