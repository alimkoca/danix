// timer.h -- Defines the interface for all PIT-related functions.
//            Written for JamesM's kernel development tutorials.

#ifndef TIMER_H
#define TIMER_H

#include "common.h"
#include <sys/types.h>

extern uint64_t tick;

void init_timer(u32int frequency);
uint64_t millis();

#endif
