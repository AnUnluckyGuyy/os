#include <stdbool.h>
#include "keyboard.h"
#include "ps2.h"
#include "scancode.h"
#include "../../cpu/io.h"
#include "../serial/serial.h"

static bool shift = false;
static bool caps = false;

char keymap[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
    [0x20] = 'd',
    [0x12] = 'e',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x17] = 'i',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x32] = 'm',
    [0x31] = 'n',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x10] = 'q',
    [0x13] = 'r',
    [0x1F] = 's',
    [0x14] = 't',
    [0x16] = 'u',
    [0x2F] = 'v',
    [0x11] = 'w',
    [0x2D] = 'x',
    [0x15] = 'y',
    [0x2C] = 'z',
    [0x02] = '1',
    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',
    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',
    [0x0B] = '0',
    [0x0C] = '-',
    [0x0D] = '=',
    [0x39] = ' ',
    [0x1C] = '\n',
    [0x0E] = '\b',
    [0x0F] = '\t',
};

unsigned char read_keyboard() {
    if (inb(PS2_STATUS_PORT) & 1) {
        unsigned char scancode = inb(PS2_DATA_PORT);

        if (scancode & SC_RELEASE) {
            if (scancode == 0xAA || scancode == 0xB6) {
                serial_print("SHIFT_KEY_UNPRESSED");
                shift = false;
            }
            return 0;
        }
        if (scancode == SC_LEFT_SHIFT || scancode == SC_RIGHT_SHIFT) {
            serial_print("SHIFT_KEY_PRESSED");
            shift = true;
            return 0;
        } else if (scancode == SC_CAPS_LOCK) {
            caps = !caps;
        }

        char c = keymap[scancode];
        if (shift || caps) {
            int offset = 32;
            if (c >= 'a' && c <= 'z') {
                return c - 32;
            }
        }
        return c;
    }
    return 0;
}