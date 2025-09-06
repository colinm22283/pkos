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
    if (argc < 2) {
        print("Invalid arguments\nUsage: ");
        print(argv[0]);
        print(" <file 1> [<file 2> ...]\n");

        return 1;
    }

    static char buf[BUFFER_SIZE];

    for (int i = 1; i < argc; i++) {
        fd_t in_fd = open(argv[i], OPEN_READ);

        if (in_fd < 0) {
            print("Unable to open \"");
            print(argv[i]);
            print("\"\n");

            return 1;
        }

        while (true) {
            int64_t amount_read = read(in_fd, buf, BUFFER_SIZE);

            if (amount_read < 0) {
                print("Unable to read \"");
                print(argv[i]);
                print("\"\n");

                return 1;
            }
            
            if (amount_read == 0) {
                break;
            }
            else {
                write(stdout, buf, amount_read);
            }
        }
    }

    return 0;
}
