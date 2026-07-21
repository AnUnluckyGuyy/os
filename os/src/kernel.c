void putchar(char c) {
	while (!(inb(0x3F8 + 5) & 0x20));

	asm volatile(
        "outb %0, %1"
        :
        : "a"(c), "Nd"(0x3F8)
	);
}

void print(char* text) {
    for (char *c = text; *c != '\0'; c++) {
    	putchar(*c);
    }
}

void kernel_main() {
    print("hello world");
    while(1);
}
