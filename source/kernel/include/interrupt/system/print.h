#pragma once

#include <bios_console.h>

__INTERRUPT_SUBROUTINE static inline void sysint_print(register char * string) {
    print_string(string);
}