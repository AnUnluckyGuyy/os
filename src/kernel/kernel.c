#include "../drivers/vga.h"
#include "../drivers/serial.h"

void kernel_main() {
    vga_print("hello world");
    serial_print("hello world");
    while(1);
}
