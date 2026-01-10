#include <stddef.h>

#include <pkos.h>

void program(void);

int main(void) {
    openat(stdout, "/dev/tty", OPEN_WRITE);
    openat(stdin, "/dev/kbd", OPEN_READ);

    write(stdout, "Booting PKOS!\n", 14);

    char c;
    read(stdin, &c, 1);

    mount("/tmp", NULL, "ramfs", 0, "");

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

