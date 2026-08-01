#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mount.h>

int main(void) {
    openat(STDOUT_FILENO, "/dev/tty0", O_WRONLY);
    openat(STDIN_FILENO, "/dev/tty0", O_RDONLY);
    openat(STDERR_FILENO, "/dev/tty0", O_WRONLY);

    write(STDOUT_FILENO, "Booting PKOS!\n", 14);

    int result;

    {
        pid_t fork_result = fork();

        if (fork_result == 0) {
            const char * args[] = { "/bin/pksh", "/etc/init.sh" };
            exec(args[0], args, 2);

            write(STDOUT_FILENO, "FAILED TO EXEC SHELL\n", 21);
        }
        else {
            exit(1);
        }
    }

    return 0;
}

