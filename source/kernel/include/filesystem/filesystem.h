#pragma once

#include <stdint.h>

#include <defs.h>

#define FILESYSTEM_ROOT_SIGNATURE ("PKFS")

enum {
    FILESYSTEM_SIGNATURE_DIRECTORY,
    FILESYSTEM_SIGNATURE_FILE,
};

typedef uint32_t filesystem_page_address_t;

typedef struct {
    filesystem_page_address_t root_page_address;
    filesystem_page_address_t root_directory_index_address;
} filesystem_t;

typedef struct __PACKED {
    char signature[4];

    filesystem_page_address_t root_directory_index_address;

    uint8_t reserved[512 - 8];
} filesystem_root_page_t;

typedef struct __PACKED {
    uint8_t signature;
    filesystem_page_address_t parent_directory_address;
    filesystem_page_address_t index_address;
    char name[503];
} filesystem_directory_page_t;
typedef struct __PACKED {
    filesystem_page_address_t parent_directory_address;
    filesystem_page_address_t next;
    filesystem_page_address_t children[126];
} filesystem_directory_index_page_t;

typedef struct __PACKED {
    uint8_t signature;
    filesystem_page_address_t parent_directory_address;
    filesystem_page_address_t index_address;
    char name[503];
} filesystem_file_page_t;
typedef struct __PACKED {

} filesystem_file_node_page_t;