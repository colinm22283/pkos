#include <stddef.h>

#include <filesystem/filesystem.h>

#include <util/string/strcmp.h>
#include <util/string/strcmpn.h>
#include <util/memory/memcpy.h>

#include <driver_table/driver_table.h>

//#include <console/print.h>
//#include <console/newline.h>
//#include <console/print_dec.h>

#include <sys/ports.h>

directory_t open_filesystem(filesystem_page_address_t root_address) {
    filesystem_root_page_t root_page;
    if (!driver_table.disc.read(root_address, 1, &root_page)) return 0;

    if (strcmpn(root_page.signature, FILESYSTEM_ROOT_SIGNATURE, 4) != 0) {
        return 0;
    }

    return root_page.root_directory_address;
}

directory_t open_directory(directory_t parent, const char * directory_name) {
    filesystem_directory_node_page_t directory_page;
    if (!driver_table.disc.read(parent, 1, &directory_page)) return 0;

    filesystem_page_address_t directory_index_address = directory_page.directory_index_address;

    while (true) {
        filesystem_directory_index_page_t directory_index;
        if (!driver_table.disc.read(directory_index_address, 1, &directory_index)) return 0;

        for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
            if (directory_index.children[i] == 0) {
                return 0;
            }
            else {
                filesystem_directory_node_page_t directory_node;
                if (!driver_table.disc.read(directory_index.children[i], 1, &directory_node)) {
                    return 0;
                }

                if (strcmp(directory_node.name, directory_name) == 0) {
                    return directory_index.children[i];
                }
            }
        }

        if (directory_index.next_index_address != 0) {
            directory_index_address = directory_index.next_index_address;
        }
        else return 0;
    }
}
file_t open_file(directory_t parent, const char * directory_name) {
    filesystem_directory_node_page_t directory_page;
    if (!driver_table.disc.read(parent, 1, &directory_page)) {
        return 0;
    }

    filesystem_page_address_t directory_index_address = directory_page.directory_index_address;

    while (true) {
        filesystem_directory_index_page_t directory_index;
        if (!driver_table.disc.read(directory_index_address, 1, &directory_index)) {
            return 0;
        }

        for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
            if (directory_index.children[i] == 0) {
                return 0;
            }
            else {
                filesystem_file_node_page_t file_node;
                if (!driver_table.disc.read(directory_index.children[i], 1, &file_node)) {
                    return 0;
                }

                if (strcmp(file_node.name, directory_name) == 0) {
                    return directory_index.children[i];
                }
            }
        }

        if (directory_index.next_index_address != 0) {
            directory_index_address = directory_index.next_index_address;
        }
        else return 0;
    }
}

bool get_directory_name(directory_t file, char * buffer) {
    filesystem_directory_node_page_t directory_node;

    if (!driver_table.disc.read(file, 1, &directory_node)) {
        return false;
    }
    uint16_t i;
    for (i = 0; i < FILESYSTEM_NAME_MAX_SIZE && directory_node.name[i] != '\0'; i++) buffer[i] = directory_node.name[i];
    buffer[i] = '\0';

    return true;
}
bool get_file_name(file_t file, char * buffer) {
    filesystem_file_node_page_t file_node;

    if (!driver_table.disc.read(file, 1, &file_node)) {
        return false;
    }
    uint16_t i;
    for (i = 0; i < FILESYSTEM_NAME_MAX_SIZE && file_node.name[i] != '\0'; i++) buffer[i] = file_node.name[i];
    buffer[i] = '\0';

    return true;
}

bool directory_iterator_init(directory_iterator_t * iterator, directory_t directory) {
    if (!driver_table.disc.read(directory, 1, &iterator->node_page)) {
        return false;
    }
    if (!driver_table.disc.read(iterator->node_page.directory_index_address, 1, &iterator->index_page)) {
        return false;
    }

    iterator->index_location = 0;

    return true;
}

filesystem_directory_entry_type_t directory_iterator_next(directory_iterator_t * iterator, filesystem_page_address_t * handle) {
    if (iterator->index_location >= FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE) {
        if (!driver_table.disc.read(iterator->index_page.next_index_address, 1, &iterator->index_page)) {
            return FS_DET_NONE;
        }

        iterator->index_location = 0;

        return directory_iterator_next(iterator, handle);
    }
    else if (iterator->index_page.children[iterator->index_location] == 0) {
        return FS_DET_NONE;
    }
    else {
        *handle = iterator->index_page.children[iterator->index_location];
        iterator->index_location++;

        filesystem_node_page_t page;

        if (!driver_table.disc.read(*handle, 1, &page)) {
            return FS_DET_NONE;
        }

        switch (page.type) {
            case FILESYSTEM_PAGE_TYPE_FILE: return FS_DET_FILE;
            case FILESYSTEM_PAGE_TYPE_DIRECTORY: return FS_DET_DIRECTORY;
            default: return FS_DET_NONE;
        }
    }
}

bool file_reader_init(file_reader_t * reader, file_t file) {
    filesystem_file_node_page_t file_node;
    if (!driver_table.disc.read(file, 1, &file_node)) {
        return false;
    }

    if (!driver_table.disc.read(file_node.root_data_address, 1, &reader->data_page)) {
        return false;
    }

    reader->data_address = file_node.root_data_address;
    reader->data_location = 0;

    return true;
}
uint32_t file_reader_read(file_reader_t * reader, char * buffer, uint32_t bytes) {
    if (reader->data_address == 0) return 0;

    uint32_t read_bytes = 0;

    while (reader->data_address != 0 && bytes > 0) {
        if (reader->data_location + bytes >= reader->data_page.size) {
            memcpy(&buffer[read_bytes], &reader->data_page.data[reader->data_location], reader->data_page.size - reader->data_location);
            read_bytes += reader->data_page.size - reader->data_location;
            bytes -= reader->data_page.size - reader->data_location;
            reader->data_location = 0;

            reader->data_address = reader->data_page.next_data_address;
            if (!driver_table.disc.read(reader->data_address, 1, &reader->data_page)) {
                return false;
            }
        }
        else {
            memcpy(&buffer[read_bytes], &reader->data_page.data[reader->data_location], bytes);
            read_bytes += bytes;
            reader->data_location += bytes;
            bytes = 0;
        }
    }

    return read_bytes;
}