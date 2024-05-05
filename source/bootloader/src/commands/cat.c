#include <commands/cat.h>

#include <console/print.h>
#include <console/newline.h>

#include <disc/filesystem.h>

#include <boot/kernel.h>

#include <memory/memcpy.h>

uint32_t cat_file(const char * path) {
    directory_t directory = open_filesystem(KERNEL_LBA_START);
    if (directory == 0) return 2;

    uint32_t base_addr = 0;
    uint32_t i;
    for (i = 0; path[i] != '\0'; i++) {
        if (path[i] == '/') {
            char buffer[FILESYSTEM_NAME_MAX_SIZE];
            memcpy(buffer, &path[base_addr], i - base_addr);
            buffer[i - base_addr] = '\0';

            directory = open_directory(directory, buffer);
            if (directory == 0) return 3;

            base_addr = i + 1;
        }
    }

    char buffer[FILESYSTEM_NAME_MAX_SIZE];
    memcpy(buffer, &path[base_addr], i - base_addr);

    file_t file = open_file(directory, buffer);
    if (file == 0) return 4;

    file_reader_t file_reader;
    file_reader_init(&file_reader, file);

    char c[2] = { 0, '\0' };
    while (file_reader_read(&file_reader, c, 1)) {
        console_print(c);
    }

    return 0;
}

__CDECL uint32_t command_cat(uint32_t argc, const char ** argv) {
    if (argc <= 1) {
        console_print("Inavlid arguments\nUsage: cat <file 1> <file 2> ... <file n>\n");
        return 1;
    }

    for (uint32_t i = 1; i < argc; i++) {
        uint32_t result = cat_file(argv[i]);
        if (result != 0) return result;
    }

    return 0;
}