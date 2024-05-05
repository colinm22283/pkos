#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>

#include <filesystem.h>
#include <write.h>
#include <page_stack.h>
#include <parse.h>

int main(int argc, const char ** argv) {
    if (argc != 3) {
        puts("Invalid arguments,\nUsage: mkfs <input directory> <output binary>");
        return 1;
    }

    const char * input_directory_path = argv[1];
    const char * output_binary_path = argv[2];

    page_stack_init();

    parse(input_directory_path);

    write_stack(output_binary_path);

    page_stack_free();

    return 0;
}