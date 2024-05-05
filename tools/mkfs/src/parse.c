#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdbool.h>

#include <parse.h>
#include <page_stack.h>

void add_file(const char * file_path, filesystem_page_address_t parent_address) {
    char file_name[FILENAME_MAX];
    for (size_t i = strlen(file_path); i > 0; i--) {
        if (file_path[i] == '/') {
            strcpy(file_name, file_path + i + 1);
            break;
        }
    }

    printf("File Name: %s\n", file_name);

    filesystem_file_node_page_t _file_node_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_FILE,
        .parent_directory_address = parent_address,
    };
    strcpy(_file_node_page.name, file_name);
    filesystem_page_address_t file_page_address = add_dir_index_entry(
        ((filesystem_directory_node_page_t *) &pages[parent_address])->directory_index_address,
        (filesystem_node_page_t *) &_file_node_page
    );

    filesystem_file_node_page_t * file_node_page = (filesystem_file_node_page_t *) &pages[file_page_address];

    filesystem_file_data_page_t _file_data_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_FILE_DATA,
        .next_data_address = 0,
        .prev_data_address = 0,
        .parent_file_address= file_page_address,
        .size = 0,
    };

    filesystem_page_address_t file_data_page_address = add_fs_page((filesystem_node_page_t *) &_file_data_page);

    filesystem_file_data_page_t * file_data_page = (filesystem_file_data_page_t *) &pages[file_data_page_address];

    file_node_page->root_data_address = file_data_page_address;

    FILE * file = fopen(file_path, "r");
    while (true) {
        char buffer[FILESYSTEM_FILE_DATA_PAGE_SIZE];
        size_t read_bytes = fread(buffer, sizeof(char), FILESYSTEM_FILE_DATA_PAGE_SIZE, file);

        if (read_bytes == 0) break;

        memcpy(file_data_page->data, buffer, read_bytes);
        file_data_page->size = read_bytes;

        if (read_bytes != FILESYSTEM_FILE_DATA_PAGE_SIZE) break;

        _file_data_page.prev_data_address = file_data_page_address;
        _file_data_page.next_data_address = 0;
        file_data_page_address = add_fs_page((filesystem_node_page_t *) &_file_data_page);
        file_data_page->next_data_address = file_data_page_address;
        file_data_page = (filesystem_file_data_page_t *) &pages[file_data_page_address];
    }
}

void recur(const char * directory_path, filesystem_page_address_t parent_address) {
    char directory_buf[PATH_MAX];
    realpath(directory_path, directory_buf);

    printf("Opening directory: %s\n", directory_buf);

    char directory_name[FILENAME_MAX];
    for (size_t i = strlen(directory_buf); i > 0; i--) {
        if (directory_buf[i] == '/') {
            strcpy(directory_name, directory_buf + i + 1);
            break;
        }
    }

    printf("Dir Name: %s\n", directory_name);

    filesystem_directory_node_page_t directory_node_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY,
        .parent_directory_address = parent_address,
    };
    strcpy(directory_node_page.name, directory_name);
    filesystem_page_address_t directory_page_address = add_dir_index_entry(
        ((filesystem_directory_node_page_t *) &pages[parent_address])->directory_index_address,
        (filesystem_node_page_t *) &directory_node_page
    );

    filesystem_directory_index_page_t directory_index_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX,
        .parent_directory_address = directory_page_address,
        .prev_index_address = 0,
    };
    for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) directory_index_page.children[i] = 0;
    filesystem_page_address_t index_page_address = add_fs_page((filesystem_node_page_t *) &directory_index_page);

    ((filesystem_directory_node_page_t *) &pages[directory_page_address])->directory_index_address = index_page_address;

    DIR * dir = opendir(directory_path);
    if (dir == NULL) exit(3);

    struct dirent * entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
        ) continue;

        char new_path_buf[PATH_MAX];
        size_t path_len = strlen(directory_path);
        memcpy(new_path_buf, directory_path, path_len * sizeof(char));
        new_path_buf[path_len] = '/';
        strcpy(new_path_buf + path_len + 1, entry->d_name);

        switch (entry->d_type) {
            case DT_REG: {
                add_file(new_path_buf, directory_page_address);
            } break;
            case DT_DIR: {
                recur(new_path_buf, directory_page_address);
            } break;
        }
    }
}

void parse(const char * input_directory_path) {
    char directory_buf[PATH_MAX];
    realpath(input_directory_path, directory_buf);

    printf("Opening directory: %s\n", directory_buf);

    char directory_name[FILENAME_MAX];
    for (size_t i = strlen(directory_buf); i > 0; i--) {
        if (directory_buf[i] == '/') {
            strcpy(directory_name, directory_buf + i + 1);
            break;
        }
    }

    printf("Dir Name: %s\n", directory_name);

    filesystem_directory_node_page_t directory_node_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY,
        .parent_directory_address = 0,
        .directory_index_address = page_count + 1,
    };
    strcpy(directory_node_page.name, directory_name);
    add_fs_page((filesystem_node_page_t *) &directory_node_page);
    filesystem_page_address_t directory_page_address = page_count - 1;

    filesystem_directory_index_page_t directory_index_page = {
        .tag.in_use = true,
        .type = FILESYSTEM_PAGE_TYPE_DIRECTORY_INDEX,
        .parent_directory_address = page_count,
        .prev_index_address = 0,
    };
    for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) directory_index_page.children[i] = 0;
    add_fs_page((filesystem_node_page_t *) &directory_index_page);

    DIR * dir = opendir(input_directory_path);
    if (dir == NULL) exit(3);

    struct dirent * entry;
    while ((entry = readdir(dir)) != NULL) {
        if (
            strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0
            ) continue;

        char new_path_buf[PATH_MAX];
        size_t path_len = strlen(input_directory_path);
        memcpy(new_path_buf, input_directory_path, path_len * sizeof(char));
        new_path_buf[path_len] = '/';
        strcpy(new_path_buf + path_len + 1, entry->d_name);

        switch (entry->d_type) {
            case DT_REG: {
                add_file(new_path_buf, directory_page_address);
            } break;
            case DT_DIR: {
                recur(new_path_buf, directory_page_address);
            } break;
        }
    }
}