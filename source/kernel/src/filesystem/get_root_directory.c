#include <filesystem/get_root_directory.h>

#include <driver_table/driver_table.h>

void get_root_directory(filesystem_t * filesystem, filesystem_directory_page_t * directory_page) {
    driver_table.disc.read(filesystem->root_directory_index_address, sizeof(filesystem_directory_page_t) / 512, directory_page);
}