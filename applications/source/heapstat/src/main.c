#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char ** argv) {
    int usage_fd = open("/sys/heap/usage", O_RD);
    int capacity_fd = open("/sys/heap/capacity", O_RD);

    char buffer[30];
    int64_t count;

    count = read(usage_fd, buffer, 30);
    if (count < 0) {
        printf("Unable to read /sys/heap/usage");
        return 1;
    }

    write(STDOUT_FILENO, buffer, count);

    printf("/");

    count = read(capacity_fd, buffer, 30);
    if (count < 0) {
        printf("Unable to read /sys/heap/capacity");
        return 1;
    }

    write(STDOUT_FILENO, buffer, count);

    printf("\n");

    return 0;
}
