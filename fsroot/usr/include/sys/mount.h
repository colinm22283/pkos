#pragma once

#include <pkos/syscalls.h>

DEFINE_SYSCALL5(SYSCALL_MOUNT, int, mount, const char *, source, const char *, target, const char *, fstype, unsigned long, flags, const char *, data);

