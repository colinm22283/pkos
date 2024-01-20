#pragma once

#include <sys/asm/hlt.h>
#include <sys/asm/cli.h>

static inline void halt() {
    cli();
    hlt();
}