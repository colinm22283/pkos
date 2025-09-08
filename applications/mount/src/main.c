#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

int main(uint64_t argc, const char ** argv) {
    if (argc != 4 && argc != 3) {
        print("Invalid arguments\nUsage: ");
        print(argv[0]);
        print(" <dst> <fs> <src>\n");

        return 1;
    }

    if (mount(
        argv[1],
        argc == 3 ? NULL : argv[3],
        argv[2],
        0,
        ""
    )) {
        print("Error while mounting\n");
        return 1;
    }

    return 0;
}
