#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, const char ** argv) {
    /* for (int i = 0; i < 1000; i++) { */
        /* int usage_fd = open("/sys/heap/usage", O_RD); */
        /* int capacity_fd = open("/sys/heap/capacity", O_RD); */

        /* char buffer[30]; */
        /* int64_t count; */

        /* count = read(usage_fd, buffer, 30); */
        /* if (count < 0) { */
            /* printf("Unable to read /sys/heap/usage"); */
            /* return 1; */
        /* } */

        /* write(STDOUT_FILENO, buffer, count); */

        /* printf("/"); */

        /* count = read(capacity_fd, buffer, 30); */
        /* if (count < 0) { */
            /* printf("Unable to read /sys/heap/capacity"); */
            /* return 1; */
        /* } */

        /* write(STDOUT_FILENO, buffer, count); */

        /* printf("\n"); */

        /* close(usage_fd); */
        /* close(capacity_fd); */

        /* if (fork() == 0) { */
            /* exit(0); */
        /* } */
    /* } */

    return 0;
}
