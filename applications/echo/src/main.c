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
    for (uint64_t i = 1; i < argc; i++) {
        print(argv[i]);
        if (i != argc - 1) print(" ");
    }
    print("\n");

    return 0;
}
