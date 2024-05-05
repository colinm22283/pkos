#include <commands/cat.h>

#include <console/print.h>
#include <console/newline.h>

#include <disc/filesystem.h>

#include <boot/kernel.h>

#include <memory/memcpy.h>

__CDECL uint32_t command_cat(uint32_t argc, const char ** argv) {
    if (argc <= 1) {
        console_print("Inavlid arguments\nUsage: cat <file 1> <file 2> ... <file n>\n");
        return 1;
    }

    directory_t directory = open_filesystem(KERNEL_LBA_START);
    if (directory == 0) return 2;

    uint32_t base_addr = 0;
    uint32_t i;
    for (i = 0; argv[1][i] != '\0'; i++) {
        if (argv[1][i] == '/') {
            char buffer[FILESYSTEM_NAME_MAX_SIZE];
            memcpy(buffer, &argv[1][base_addr], i - base_addr);
            buffer[i - base_addr] = '\0';

            directory = open_directory(directory, buffer);
            if (directory == 0) return 3;

            base_addr = i + 1;
        }
    }

    char buffer[FILESYSTEM_NAME_MAX_SIZE];
    memcpy(buffer, &argv[1][base_addr], i - base_addr);

    file_t file = open_file(directory, buffer);
    if (file == 0) return 4;

    file_reader_t file_reader;
    file_reader_init(&file_reader, file);

    char c[2] = { 0, '\0' };
    while (file_reader_read(&file_reader, c, 1)) {
        console_print(c);
    }
    console_newline();

    return 0;
}