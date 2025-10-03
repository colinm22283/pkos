#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

int main(uint64_t argc, const char ** argv) {
    fd_t usage_fd = open("/sys/heap/usage", OPEN_READ);
    fd_t capacity_fd = open("/sys/heap/capacity", OPEN_READ);

    char buffer[30];
    int64_t count;

    count = read(usage_fd, buffer, 30);
    if (read < 0) {
        print("Unable to read /sys/heap/usage");
        return 1;
    }

    write(stdout, buffer, count);

    print("/");

    count = read(capacity_fd, buffer, 30);
    if (read < 0) {
        print("Unable to read /sys/heap/capacity");
        return 1;
    }

    write(stdout, buffer, count);

    print("\n");

    return 0;
}
