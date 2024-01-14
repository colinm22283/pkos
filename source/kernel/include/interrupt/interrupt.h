#pragma once

static inline void wait_for_interrupt(void) { asm volatile ("hlt"); }