#include <stddef.h>

#include <pkos.h>

void page_fault_handler(signal_number_t sig) {
    write(stdout, "RECEIVED PAGE FAULT!!!!\n", 24);

    while (1) {}
}

int main(void) {
    openat(stdout, "/dev/tty0", OPEN_WRITE);
    openat(stdin, "/dev/tty0", OPEN_READ);

    write(stdout, "Booting PKOS!\n", 14);

    mount("/tmp", NULL, "ramfs", 0, "");

    // if (signal(SIG_PAGE, page_fault_handler) != ERROR_OK) {
    //     write(stdout, "oh dear\n", 8);
    //     return 1;
    // }

    // *(char *) 0 = 10;

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

