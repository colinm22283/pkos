#pragma once

#include <stdint.h>

#include <defs.h>

#define FILESYSTEM_ROOT_SIGNATURE ("PKFS")

#define FILESYSTEM_NAME_MAX_SIZE (128)

enum {
    FILESYSTEM_PAGE_TYPE_FILE,
    FILESYSTEM_PAGE_TYPE_DIRECTORY,
};

typedef uint8_t filesystem_page_padding_t[512];

typedef uint32_t filesystem_page_address_t;
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
        char name[FILESYSTEM_NAME_MAX_SIZE];
    };

    filesystem_page_padding_t _padding;
} filesystem_node_page_t;

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

        filesystem_page_address_t next;
        filesystem_page_address_t children[512 / sizeof(filesystem_page_address_t) - sizeof(filesystem_page_address_t)];
    };

    filesystem_page_padding_t _padding;
} filesystem_directory_index_page_t;

typedef union __PACKED {
    struct __PACKED {
        filesystem_page_tag_t tag;
        filesystem_page_type_t type;
        char name[FILESYSTEM_NAME_MAX_SIZE];

        filesystem_page_address_t parent_directory_address;
        filesystem_page_address_t directory_index_address;
    };

    filesystem_page_padding_t _padding;
} filesystem_file_node_page_t;