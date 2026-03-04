#pragma once

#include <sys/types.h>

#include <pkos/syscalls.h>

#define F_OK 0
#define F_RDLCK 0
#define F_WRLCK 0
#define F_SETLKW 0

#define O_RDONLY  0b0001
#define O_RD      0b0001
#define O_WRONLY  0b0010
#define O_WR      0b0010
#define O_RDWR    0b0011

#define O_CREAT   0b0100
#define O_TMPFILE 0b1000
#define O_TRUNC 0

#define S_IRUSR 0
#define S_IWUSR 0

struct flock {
    int l_whence, l_start, l_len, l_pid, l_type;
};

static inline int open(const char * path, int flags, ... /* mode_t mode */) {
    mode_t mode = 0;

    if (flags & O_CREAT || flags & O_TMPFILE) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int r;
    asm volatile ("int $0x30" : "=a" (r) : "a" (SYSCALL_OPEN), "S" ((int64_t) path), "d" ((int64_t) flags), "c" ((int64_t) mode) : "memory", "cc"); \
    return r;
}

DEFINE_SYSCALL3(SYSCALL_OPENAT, int, openat, int, dirfd, const char *, path, int, flags);

