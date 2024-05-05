#include <stdio.h>

#include <write.h>
#include <page_stack.h>
#include <config.h>

void write_stack(const char * path) {
    if (root_page.root_directory_address != 0) root_page.root_directory_address += FS_ROOT_OFFSET;
    root_page.first_free = FS_ROOT_OFFSET + 1 + page_count;

    for (uint64_t i = 0; i < page_count; i++) {
        switch (pages[i].type) {
            case FILESYSTEM_PAGE_TYPE_FILE: {
                filesystem_file_node_page_t * page = (filesystem_file_node_page_t *) &pages[i];

                if (page->parent_directory_address != 0) page->parent_directory_address += FS_ROOT_OFFSET + 1;
                if (page->root_data_address != 0) page->root_data_address += FS_ROOT_OFFSET + 1;
            } break;
            case FILESYSTEM_PAGE_TYPE_FILE_DATA: {
                filesystem_file_data_page_t * page = (filesystem_file_data_page_t *) &pages[i];

                if (page->parent_file_address != 0) page->parent_file_address += FS_ROOT_OFFSET + 1;
                if (page->prev_data_address != 0) page->prev_data_address += FS_ROOT_OFFSET + 1;
                if (page->next_data_address != 0) page->next_data_address += FS_ROOT_OFFSET + 1;
            } break;
            case FILESYSTEM_PAGE_TYPE_DIRECTORY: {
                filesystem_directory_node_page_t * page = (filesystem_directory_node_page_t *) &pages[i];

                if (page->parent_directory_address != 0) page->parent_directory_address += FS_ROOT_OFFSET + 1;
                if (page->directory_index_address != 0) page->directory_index_address += FS_ROOT_OFFSET + 1;
            } break;
            case FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX: {
                filesystem_directory_index_page_t * page = (filesystem_directory_index_page_t *) &pages[i];

                if (page->parent_directory_address != 0) page->parent_directory_address += FS_ROOT_OFFSET + 1;
                if (page->prev_index_address != 0) page->prev_index_address += FS_ROOT_OFFSET + 1;
                if (page->next_index_address != 0) page->next_index_address += FS_ROOT_OFFSET + 1;

                for (size_t j = 0; j < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; j++) {
                    if (page->children[j] != 0) page->children[j] += FS_ROOT_OFFSET + 1;
                }
            }
        }
    }

    FILE * out_file = fopen(path, "w");

    fwrite(&root_page, sizeof(filesystem_root_page_t), 1, out_file);
    fwrite(pages, sizeof(filesystem_node_page_t), page_count, out_file);

    fclose(out_file);
}