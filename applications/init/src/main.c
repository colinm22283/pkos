#include <stddef.h>

#include <pkos.h>

int main(void) {
    openat(stdout, "/dev/tty0", OPEN_WRITE);
    openat(stdin, "/dev/tty0", OPEN_READ);

    write(stdout, "Booting PKOS!\n", 14);

    mount("/tmp", NULL, "ramfs", 0, "");

    mount("/proc", NULL, "procfs", 0, "");

    {
        pid_t fork_result = fork();

        if (fork_result == 0) {
            write(stdout, "Child!\n", 7);

            const char * args[] = { "/bin/pksh" };
            exec("/bin/pksh", args, 1);
        }
        else {
            write(stdout, "Parent!\n", 8);

            exit(1);
        }
    }

    while (1) {}

    return 0;
}

