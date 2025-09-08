#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

int main(uint64_t argc, const char ** argv) {
    if (argc == 1) return 1;

    for (int i = 1; i < argc; i++) {
        fd_t fd = open(argv[i], OPEN_WRITE | OPEN_CREATE);

        close(fd);
    }

    return 0;
}
