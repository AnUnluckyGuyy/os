#include "../drivers/screen/vga.h"
#include "../drivers/serial/serial.h"
#include "../drivers/keyboard/keyboard.h"

void kernel_main() {
    vga_init();
    vga_disable_cursor();
    vga_print("hello world");
    serial_print("hello world");
    char c;
    while(1) {
        c = read_keyboard();

        if (c != 0) {
            vga_putchar(c);
            serial_putchar(c);
        }
    }
}
