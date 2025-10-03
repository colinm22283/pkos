#include <pkos.h>

int main(void) {
    fd_t fd = open("/dev/tty", OPEN_WRITE);

    char c;
    read(stdin, &c, 1);
    read(stdin, &c, 1);
    read(stdin, &c, 1);

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

    {
        pid_t fork_result = fork();

        if (fork_result == 0) {
            const char * args[] = { "/bin/sh" };
            exec("/bin/sh", args, 1);
        }
    }

    return 0;
}

