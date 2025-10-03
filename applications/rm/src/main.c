#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#define BUFFER_SIZE (1024)

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

int main(uint64_t argc, const char ** argv) {
    if (argc <= 1) {
        print("Invalid arguments\nUsage: ");
        print(argv[0]);
        print(" <file 1> <file 2> ...\n");

        return 1;
    }

    for (uint64_t i = 1; i < argc; i++) remove(argv[i]);

    return 0;
}
