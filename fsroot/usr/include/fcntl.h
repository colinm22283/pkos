#pragma once

#include <pkos/syscalls.h>

#define F_OK 0
#define F_RDLCK 0
#define F_WRLCK 0
#define F_SETLKW 0

#define O_RDONLY 0b01
#define O_RD     0b01
#define O_WRONLY 0b10
#define O_WR     0b10
#define O_RDWR   0b11

#define O_CREAT 0b100
#define O_TRUNC 0

#define S_IRUSR 0
#define S_IWUSR 0

struct flock {
    int l_whence, l_start, l_len, l_pid, l_type;
};

DEFINE_SYSCALL2(SYSCALL_OPEN, int, open, const char *, path, int, flags);
DEFINE_SYSCALL3(SYSCALL_OPENAT, int, openat, int, dirfd, const char *, path, int, flags);

