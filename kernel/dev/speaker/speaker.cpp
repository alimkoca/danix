//
// speaker.cpp
//
// created at 01/04/2021 14:48:20
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

#include "speaker.h"

void init_speaker() {
	outb(0x61, inb(0x61) | 0x1);
}

void speaker_play(uint32_t hz) {
	uint32_t Div;
 	uint8_t tmp;

 	Div = 1193180 / hz;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));

 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
}

void speaker_stop() {
	uint8_t tmp = inb(0x61) & 0xFC;
 	outb(0x61, tmp);
}

void speaker_beep(uint32_t hz, uint64_t len) {
	speaker_play(hz);
	usleep(len);
	speaker_stop();
}

void victory_beep() {
	speaker_beep(600, 500);
}

void bell_beep() {
	// speaker_beep(600, 60);
	speaker_beep(1100, 60);
}

// #if defined(__cplusplus)
}
// #endif // __cplusplus
