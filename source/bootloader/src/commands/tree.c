#pragma once

#include <commands/tree.h>

#include <disc/filesystem.h>

#include <boot/kernel.h>

#include <console/print.h>
#include <console/put.h>
#include <console/newline.h>

void recur(directory_t directory, uint8_t indent) {
    directory_iterator_t iterator;
    directory_iterator_init(&iterator, directory);

    filesystem_directory_entry_type_t type = 0;
    filesystem_page_address_t address;

    while ((type = directory_iterator_next(&iterator, &address)) != FS_DET_NONE) {
        if (type == FS_DET_FILE) {
            char name_buffer[FILESYSTEM_NAME_MAX_SIZE + 1];
            get_file_name(address, name_buffer);

            for (uint8_t i = 0; i < indent; i++) console_put(' ');
//            console_print("<FILE> ");
            console_print(name_buffer);
            console_newline();
        }
        else if (type == FS_DET_DIRECTORY) {
            char name_buffer[FILESYSTEM_NAME_MAX_SIZE + 1];
            get_directory_name(address, name_buffer);

            for (uint8_t i = 0; i < indent; i++) console_put(' ');
//            console_print("<DIR>  ");
            console_print(name_buffer);
            console_newline();

            recur(address, indent + 2);
        }
    }
}

__CDECL uint32_t command_tree(__UNUSED uint32_t argc, __UNUSED const char ** argv) {
    directory_t root_directory = open_filesystem(KERNEL_LBA_START);

    if (root_directory == 0) {
        console_print("Error opening filesystem\n");
        return 1;
    }

    console_print("/\n");

    recur(root_directory, 2);

    return 0;
}