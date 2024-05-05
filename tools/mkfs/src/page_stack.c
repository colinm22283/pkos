#include <stdbool.h>
#include <stdlib.h>

#include <page_stack.h>

filesystem_root_page_t root_page = {
    .tag.in_use = true,
    .signature = FILESYSTEM_ROOT_SIGNATURE,
    .root_directory_address = 1,
};
filesystem_node_page_t * pages;
uint64_t page_count;
uint64_t page_capacity;

void page_stack_init() {
    pages = malloc(sizeof(filesystem_node_page_t));
    page_count = 0;
    page_capacity = 1;
}

void page_stack_free() {
    free(pages);
}

filesystem_page_address_t add_fs_page(filesystem_node_page_t * page) {
    pages[page_count] = *page;

    page_count++;

    if (page_count == page_capacity) {
        page_capacity *= 2;
        pages = realloc(pages, page_capacity * sizeof(filesystem_node_page_t));

        if (pages == NULL) {
            exit(2);
        }
    }

    return page_count - 1;
}

void add_dir_index_entry_recur(filesystem_page_address_t index_address, filesystem_page_address_t page_address) {
    filesystem_directory_index_page_t * index = (filesystem_directory_index_page_t *) &pages[index_address];

    if (index->children[FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE - 1] != 0) {
        if (index->next_index_address == 0) {
            filesystem_directory_index_page_t index_page = {
                .tag.in_use = true,
                .type = FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX,
                .prev_index_address = index_address,
                .next_index_address = 0,
                .parent_directory_address = index->parent_directory_address,
            };
            index_page.children[0] = page_address;
            for (int i = 1; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) index_page.children[i] = 0;

            add_fs_page(&index_page);
        }
        else {
            add_dir_index_entry_recur(index->next_index_address, page_address);
        }
    } else {
        for (int i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
            if (index->children[i] == 0) {
                index->children[i] = page_address;
                break;
            }
        }
    }
}

filesystem_page_address_t add_dir_index_entry(filesystem_page_address_t index_address, filesystem_node_page_t * page) {
    add_fs_page(page);

    filesystem_page_address_t page_address = page_count - 1;

    add_dir_index_entry_recur(index_address, page_count - 1);

    return page_address;
}