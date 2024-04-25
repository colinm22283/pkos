#pragma once

#include <stdbool.h>

#include <sys/asm/hlt.h>
#include <sys/asm/cli.h>

__NORETURN static inline void halt() {
    cli();
    while (true) {
        hlt();
    }
}