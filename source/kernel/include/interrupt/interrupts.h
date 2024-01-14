#pragma once

#include <stdint.h>

#include <defs.h>

#include <interrupt/interrupt.h>

extern __NORETURN void null_pic1_handler_entry();
extern __NORETURN void null_pic2_handler_entry();
extern __NORETURN void unimp_handler_entry();

extern __NORETURN void system_interrupt_handler_entry();
extern __NORETURN void gpf_handler_entry();
extern __NORETURN void page_fault_handler_entry();

extern __NORETURN void keyboard_handler_entry();