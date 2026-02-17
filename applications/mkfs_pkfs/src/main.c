#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <pkos.h>
#include <error_number.h>

#include <filesystem.h>

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

    static filesystem_root_page_t root_page = {
        .first_free = 1,
        .root_directory_address = 1,
        .signature = FILESYSTEM_ROOT_SIGNATURE,
        .tag = {
            .in_use = 1,
        },
    };

    static filesystem_directory_node_page_t root_directory = {
        .name = "fsroot",
        .directory_index_address = 2,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY,
        .parent_directory_address = 1,
        .tag = {
            .in_use = 1,
        },
    };

    static filesystem_directory_index_page_t root_index = {
        .next_index_address = 0,
        .prev_index_address = 0,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX,
        .parent_directory_address = 1,
        .tag = {
            .in_use = 1,
        },
    };

    for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
        root_index.children[i] = 0;
    }

    fd_t out_fd = open(argv[1], OPEN_WRITE | OPEN_CREATE);

    if (out_fd < 0) {
        print("Unable to open '");
        print(argv[1]);
        print("'\n");
    }

    write(out_fd, (char *) &root_page, sizeof(filesystem_root_page_t));
    write(out_fd, (char *) &root_directory, sizeof(filesystem_directory_node_page_t));
    write(out_fd, (char *) &root_index, sizeof(filesystem_directory_index_page_t));

    return 0;
}
