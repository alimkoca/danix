//
// keyboard.cpp
//
// created at 27/03/2021 10:07:53
// written by llamaking136
//

// MIT License
//     
// Copyright (c) 2021 llamaking136
//     
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//     
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//     
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


// #if defined(__cplusplus)
extern "C" {
// #endif // __cplusplus

#include "keyboard.hpp"

uint8_t current_char = '\0';

uint8_t keyboard_map[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b',
    '\t',
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0,
    '*',
    0,
    ' ',
    0,
    0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0,
    0,
    0,
    0,
    0,
    0,
    '-',
    0,
    0,
    0,
    '+',
    0,
    0,
    0,
    0,
    0,
    0, 0, 0,
    0,
    0,
    0
};

// uint32_t current_location = 0;

/*
void getch() {
	uint8_t keycode = inb(0x60);

	if (keyboard_map[(unsigned char)keycode] != 0) {
		putc(keyboard_map[(unsigned char)keycode]);
	} else {
		return;
	}

	outb(0x20, 0x20);
}
*/

void init_keyboard() {
	// keyboard_enable();
	register_interrupt_handler(IRQ1, keyboard_handler, "keyboard");
}

void keyboard_enable() {
	outb(0x61, inb(0x61) & 0x7f);
}

void keyboard_disable() {
	outb(0x61, inb(0x61) | 0x80);
}

void keyboard_restart() {
	keyboard_disable();
	keyboard_enable();
}

static void keyboard_handler(registers_t regs) {
	uint8_t scancode = inb(0x60);
	/*
    if (scancode == 0x2A) {
    	shift_key = 1;
    } else if (scancode & 0xAA) {
   		int shift_key= 0;
    } else {
        if (scancode & 0x80) {
            int shiftaltctrl = 1;
        } else {
        	printf("%c", keyboard_map[scancode]);
        }
    }
	*/
	if (keyboard_map[scancode] != 0) {
		// putc(keyboard_map[scancode], f_white);
		current_char = keyboard_map[scancode];
	}
}

uint8_t __getch(int verbose) {
	// uint8_t result = keyboard_map[inb(0x60)];
	// return result ? result : '\0';
	while (current_char == '\0');
	uint8_t temp = current_char;
	current_char = '\0';
	if (verbose) {
		putc(temp, f_white);
	}
	return temp;
}

// #if defined(__cplusplus)
}
// #endif // __cplusplus
