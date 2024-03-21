#pragma once

#include <stddef.h>

#include <driver_table/driver_table.h>

typedef struct {
    filesystem_directory_index_page_t index_page;
    uint8_t child_index;
} filesystem_directory_iterator_t;

static inline bool filesystem_directory_iterator_generate(filesystem_directory_page_t * directory, filesystem_directory_iterator_t * iterator) {
    if (!driver_table.disc.read(directory->index_address, 1, &iterator->index_page)) return false;

    iterator->child_index = 0;

    return true;
}

static inline bool filesystem_directory_iterator_get(filesystem_directory_iterator_t * iterator, void * result) {
    if (iterator->child_index == 0xFF) return false;

    driver_table.disc.read(iterator->index_page.children[iterator->child_index], 1, result);

    return true;
}

static inline bool filesystem_directory_iterator_ok(filesystem_directory_iterator_t * iterator) {
    return iterator->child_index != 0xFF;
}

static inline bool filesystem_directory_iterator_next(filesystem_directory_iterator_t * iterator) {
    if (iterator->child_index == 0xFF) return false;

    if (iterator->child_index == 126) {
        if (iterator->index_page.next == 0) return false;

        driver_table.disc.read(iterator->index_page.next, 1, &iterator->index_page);
        iterator->child_index = 0;
        return true;
    }
    else {
        iterator->child_index++;
        return iterator->index_page.children[iterator->child_index] != 0;
    }
}