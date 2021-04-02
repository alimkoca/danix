//
// assembly.cpp
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

#include "assembly.h"

uint8_t inb(uint16_t port) {
	uint8_t r;
	asm volatile("inb %1, %0"
        : "=a"(r)
        : "Nd"(port));
	return r;
}

uint32_t inl(uint16_t port) {
	uint32_t ret;
    asm volatile("in %%dx,%%eax"
        : "=a"(ret)
        : "d"(port));
    return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile("inw %1, %0" 
		: "=a" (ret) 
		: "dN" (port));
	return ret;
}

void outb(uint16_t port, uint8_t value) {
	asm volatile("outb %0, %1"
        :
        : "a"(value), "Nd"(port)
        :);
}

void outl(uint16_t port, uint32_t value) {
	asm volatile("out %%eax,%%dx" 
		:
		: "a"(value), "d"(port));	
}

void outw(uint16_t port, uint16_t value) {
	asm volatile("outw %%ax,%%dx"
        :
        : "dN"(port), "a"(value));	
}

void sti() {
	asm volatile("sti");
}

// #if defined(__cplusplus)
}
// #endif // __cplusplus
