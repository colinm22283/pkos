#include <pkos.h>

int main(void) {
    fd_t fd = openat(stdout, "/dev/tty", OPEN_WRITE);
    fd_t infd = openat(stdin, "/dev/kbd", OPEN_READ);

    write(fd, "Booting PKOS!\n", 14);

    /* write(fd, "Heap usage: ", 12); */
    /* { */
        /* pid_t fork_result = fork(); */

        /* if (fork_result == 0) { */
            /* const char * args[] = { "/bin/heapstat" }; */
            /* exec("/bin/heapstat", args, 1); */

            /* exit(1); */
        /* } */
    /* } */

    char c;
    read(infd, &c, 1);

    {
        pid_t fork_result = fork();

        if (fork_result == 0) {
            write(stdout, "Child!\n", 7);

            const char * args[] = { "/bin/pksh" };
            exec("/bin/sh", args, 1);
        }
        else {
            write(stdout, "Parent!\n", 8);

            exit(1);
        }
    }

    while (1) {}

    return 0;
}

