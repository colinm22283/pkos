#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <pkos.h>
#include <error_number.h>

int command_position;
char command_buffer[512];

uint64_t strcmp(const char * a, const char * b);

uint64_t strlen(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;
    return str_size;
}

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

void list_dir(const char * path, int indent) {
    if (indent == 50) {
        print("Max reached\n");
        return;
    }

    fd_t dir_fd = open(path, OPEN_READ);
    if (dir_fd < 0) {
        print("Unable to open directory: ");
        print(path);
        print("\n");
        return;
    }

    char * buffer = map(0, NULL, 512, 0, MAP_ANON | MAP_WRITE);
    int64_t readdir_result = readdir(dir_fd, (directory_entry_t *) buffer, 512);

    if (readdir_result < 0) {
        print("Error listing directory: ");
        print(path);
        print("\n");
        return;
    }

    int64_t offset = 0;
    while (true) {
        if (offset >= readdir_result) break;

        directory_entry_t * entry = (directory_entry_t *) (buffer + offset);
        for (int i = 0; i < indent; i++) write(stdout, "| ", 2);
        print(entry->name);
        print("\n");

        if (entry->file_type == FS_DIRECTORY) {

            uint64_t path_size = strlen(path);
            uint64_t name_size = strlen(entry->name);

            char buf[1024];
            for (uint64_t i = 0; i < path_size; i++) buf[i] = path[i];
            buf[path_size] = '/';
            for (uint64_t i = 0; i < name_size; i++) buf[path_size + i + 1] = entry->name[i];
            buf[path_size + 1 + name_size] = '\0';

            list_dir(buf, indent + 1);
        }

        offset += (int64_t) entry->struct_size;
    }

    if (close(dir_fd) < 0) {
        print("Error closing directory: ");
        print(path);
        print("\n");
        return;
    }
}

int main(uint64_t argc, const char ** argv) {
    if (argc == 2) {
        print(argv[1]);
        print("\n");

        list_dir(argv[1], 1);
    }
    else if (argc == 1) {
        print(".\n");

        list_dir(".", 1);
    }
    else {
        print("Invalid arguments!\n");
        return 1;
    }

    return 0;
}
