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
    if (argc != 2) {
        print("Invalid arguments\nUsage: ");
        print(argv[0]);
        print(" <path>\n");

        return 1;
    }

    if (mkdir(argv[1])) {
        print("Error while creating directory\n");
        return 1;
    }

    return 0;
}
