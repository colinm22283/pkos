#include <pkos.h>

int main(void) {
    fd_t fd = open("/dev/tty", OPEN_WRITE);

    write(fd, "Booting PKOS!\n", 14);

    pid_t fork_result = fork();

    if (fork_result == 0) {
        const char * args[] = { "/bin/sh" };
        exec("/bin/sh", args, 1);
    }

    return 0;
}

