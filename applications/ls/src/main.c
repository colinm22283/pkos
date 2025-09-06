#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#define BUFFER_SIZE (10)

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

int main(uint64_t argc, const char ** argv) {
    const char * path;
    if (argc == 1) path = ".";
    else if (argc == 2) path = argv[1];
    else {
        print("Invalid arguments\nUsage: ");
        print(argv[0]);
        print(" [<dir>]\n");
    }

    fd_t dir_fd = open(path, OPEN_READ);

    if (dir_fd < 0) {
        print("Unable to open directory\n");
        return 1;
    }

    char buffer[512];
    int64_t readdir_result = readdir(dir_fd, (directory_entry_t *) buffer, 512);

    int64_t offset = 0;
    while (true) {
        if (offset >= readdir_result) break;

        directory_entry_t * entry = (directory_entry_t *) (buffer + offset);
        print(entry->name);
        print("\n");

        offset += (int64_t) entry->struct_size;
    }

    return 0;
}
