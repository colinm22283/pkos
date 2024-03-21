#pragma once

#include <stdbool.h>

#include <filesystem/filesystem.h>

enum {
    RESULT_FILESYSTEM_INIT_SUCCESS,
    RESULT_FILESYSTEM_INIT_DISC_READ_ERROR,
    RESULT_FILESYSTEM_INIT_INVALID_SIGNATURE,
};

uint64_t filesystem_init(filesystem_t * filesystem, filesystem_page_address_t base_address);