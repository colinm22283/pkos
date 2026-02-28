#include <stddef.h>

#include <sys/types.h>

#include <pkos/syscalls.h>
#include <pkos/fileno.h>

DEFINE_SYSCALL1(SYSCALL_ALARM, unsigned int, alarm, unsigned int, time);
DEFINE_SYSCALL1(SYSCALL_CLOSE, int, close, int, fd);
DEFINE_SYSCALL3(SYSCALL_READ, ssize_t, read, int, fd, char *, buffer, size_t, size);
DEFINE_SYSCALL3(SYSCALL_WRITE, ssize_t, write, int, fd, const char *, buffer, size_t, size);

static inline __attribute__((noreturn)) void exit(int status) {
    uint64_t ret;

    asm volatile ("int $0x30" : "=a" (ret) : "a" (SYSCALL_EXIT), "S" ((int64_t) status) : "memory", "cc");

    __builtin_unreachable();
}

// pid_t fork(void);
// pid_t getpid(void);

int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);

