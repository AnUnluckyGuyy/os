#include "keyboard.h"
#include "../cpu/io.h"

char keymap[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
    [0x20] = 'd',
    [0x12] = 'e',
    [0x21] = 'f',
};

unsigned char read_keyboard() {
    if (inb(0x64) & 1) {
        unsigned char scancode = inb(0x60);

        if (scancode & 0x80) {
            return 0;
        }

        return keymap[scancode];
    }
    return 0;
}