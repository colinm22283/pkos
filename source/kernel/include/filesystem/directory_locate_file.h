#pragma once

#include <filesystem/directory_locate.h>

static inline bool filesystem_directory_locate_file(filesystem_directory_page_t * directory, const char * name, filesystem_directory_page_t * found_directory) {
    if (!filesystem_directory_locate(directory, name, found_directory)) return false;
    return found_directory->signature == FILESYSTEM_SIGNATURE_FILE;
}