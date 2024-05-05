#pragma once

#include <stdint.h>

#include <defs.h>

#define FILESYSTEM_ROOT_SIGNATURE ("PKFS")

#define FILESYSTEM_NAME_MAX_SIZE (128)
#define FILESYSTEM_FILE_DATA_PAGE_SIZE (512 - sizeof(filesystem_page_tag_t) - sizeof(filesystem_page_type_t) - 3 * sizeof(filesystem_page_address_t) - sizeof(uint16_t))
#define FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE ((512 - sizeof(filesystem_page_tag_t) - sizeof(filesystem_page_type_t) - 3 * sizeof(filesystem_page_address_t)) / sizeof(filesystem_page_address_t))

enum {
    FILESYSTEM_PAGE_TYPE_FILE,
    FILESYSTEM_PAGE_TYPE_FILE_DATA,
    FILESYSTEM_PAGE_TYPE_DIRECTORY,
    FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX,
};

typedef uint8_t filesystem_page_padding_t[512];

typedef uint64_t filesystem_page_address_t;
typedef uint8_t filesystem_page_type_t;

typedef struct __PACKED {
    uint8_t in_use    : 1;
    uint8_t _reserved : 7;
} filesystem_page_tag_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        const char signature[4];

        filesystem_page_address_t root_directory_address;
        filesystem_page_address_t first_free;
    };

    filesystem_page_padding_t _padding;
} filesystem_root_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;
    };

    filesystem_page_padding_t _padding;
} filesystem_node_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;
        char name[FILESYSTEM_NAME_MAX_SIZE];

        filesystem_page_address_t parent_directory_address;
        filesystem_page_address_t root_data_address;
    };

    filesystem_page_padding_t _padding;
} filesystem_file_node_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;

        filesystem_page_address_t parent_file_address;
        filesystem_page_address_t prev_data_address;
        filesystem_page_address_t next_data_address;

        uint16_t size;

        char data[512 - sizeof(filesystem_page_tag_t) - sizeof(filesystem_page_type_t) - 3 * sizeof(filesystem_page_address_t) - sizeof(uint16_t)];
    };

    filesystem_page_padding_t _padding;
} filesystem_file_data_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;
        char name[FILESYSTEM_NAME_MAX_SIZE];

        filesystem_page_address_t parent_directory_address;
        filesystem_page_address_t directory_index_address;
    };

    filesystem_page_padding_t _padding;
} filesystem_directory_node_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;

        filesystem_page_address_t parent_directory_address;
        filesystem_page_address_t prev_index_address;
        filesystem_page_address_t next_index_address;
        filesystem_page_address_t children[FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE];
    };

    filesystem_page_padding_t _padding;
} filesystem_directory_index_page_t;