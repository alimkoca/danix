//
// panic.c
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


#include "panic.h"

void __panic(char* file, const char* func, int line, string str, ...) {
	// printc(str, f_white);
	
#if defined(BEEP)
	speaker_play(1230);
#endif // BEEP

	asm volatile("cli");

	uint32_t i;
	char* s;
	
	colors current_color = f_white;

	va_list arg;
	va_start(arg, str);

	colors reset_color = f_white;

	printf("\33RKERNEL PANIC\33r: ");

	while (*str) {
		if (*str == '%') { // formating chars
			str++;
			switch (*str) {
				case 'c':
					i = va_arg(arg, int);
					putc(i, current_color);
					break;
				case 'd':
					i = va_arg(arg, int);
					if (i < 0) {
						i = -i;
						putc('-', current_color);
					}
					printc(strconv(i, 10), current_color);
					break;
				case 's':
					s = va_arg(arg, char*);
					printc(s, current_color);
					break;
				case 'x':
					i = va_arg(arg, uint32_t);
					printc("0x", current_color);
					printc(strconv(i, 16), current_color);
					break;
				case 'o':
					i = va_arg(arg, uint32_t);
					printc(strconv(i, 8), current_color);
					break;
				defualt:
					putc('%', current_color);
			}
		} else if (*str == '\33') { // colors
			*str++;
			switch (*str) {
				case 'W':
					current_color = f_white;
					break;
				case 'R':
					current_color = f_red;
					break;
				case 'G':
					current_color = f_green;
					break;
				case 'B':
					current_color = f_blue;
					break;
				case 'r':
					current_color = reset_color;
					break;
				default:
					break;
			}
		} else { // basic chars
			putc(*str, current_color);
		}
		str++;
	}
	printf("\nDebug info:\n\tTime since awake: %dms\n", millis());
	if (current_module != "") {
		printf("\tOccured in module (or last known): %s\n", current_module);
	}
	printf("\tFile: %s\n\tFunction: %s\n\tLine: %d", file, func, line);
	for (;;);
}
