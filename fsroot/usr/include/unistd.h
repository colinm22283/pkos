#include <stddef.h>

#include <sys/types.h>

#include <pkos/syscalls.h>

// pid_t fork(void);
// pid_t getpid(void);

int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);

