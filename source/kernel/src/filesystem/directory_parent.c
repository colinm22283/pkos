#include <filesystem/directory_parent.h>

#include <driver_table/driver_table.h>

bool filesystem_directory_parent(filesystem_directory_page_t * directory, filesystem_directory_page_t * result) {
    if (directory->parent_directory_address == 0) return false;

    return driver_table.disc.read(directory->parent_directory_address, 1, result);
}