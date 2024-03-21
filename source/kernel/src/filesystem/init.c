#include <filesystem/init.h>

#include <util/string/strcmpn.h>

#include <driver_table/driver_table.h>

uint64_t filesystem_init(filesystem_t * filesystem, filesystem_page_address_t base_address) {
    filesystem_root_page_t root_page;
    if (!driver_table.disc.read(base_address, 1, &root_page)) return RESULT_FILESYSTEM_INIT_DISC_READ_ERROR;

    if (strcmpn(root_page.signature, FILESYSTEM_ROOT_SIGNATURE, 4) != 0) return RESULT_FILESYSTEM_INIT_INVALID_SIGNATURE;

    filesystem->root_page_address = base_address;
    filesystem->root_directory_index_address = root_page.root_directory_index_address;

    return RESULT_FILESYSTEM_INIT_SUCCESS;
}