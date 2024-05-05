#include <stddef.h>

#include <disc/filesystem.h>
#include <disc/read.h>

#include <string/strcmp.h>
#include <string/strcmpn.h>

#include <console/print.h>
#include <console/newline.h>
#include <console/print_dec.h>

#include <sys/ports.h>

directory_t open_filesystem(filesystem_page_address_t root_address) {
    filesystem_root_page_t root_page;
    disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, root_address, 1, (void *) &root_page);

    if (strcmpn(root_page.signature, FILESYSTEM_ROOT_SIGNATURE, 4) != 0) {
        return 0;
    }

    return root_page.root_directory_address;
}

directory_t open_directory(directory_t parent, const char * directory_name) {
    filesystem_directory_node_page_t directory_page;
    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, parent, 1, (void *) &directory_page)) {
        return 0;
    }

    filesystem_page_address_t directory_index_address = directory_page.directory_index_address;

    while (true) {
        filesystem_directory_index_page_t directory_index;
        if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, directory_index_address, 1, (void *) &directory_index)) {
            return 0;
        }

        for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
            if (directory_index.children[i] == 0) {
                return 0;
            }
            else {
                filesystem_directory_node_page_t directory_node;
                if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, directory_index.children[i], 1, (void *) &directory_node)) {
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
    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, parent, 1, (void *) &directory_page)) {
        return 0;
    }

    filesystem_page_address_t directory_index_address = directory_page.directory_index_address;

    while (true) {
        filesystem_directory_index_page_t directory_index;
        if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, directory_index_address, 1, (void *) &directory_index)) {
            return 0;
        }

        for (size_t i = 0; i < FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE; i++) {
            if (directory_index.children[i] == 0) {
                return 0;
            }
            else {
                filesystem_file_node_page_t file_node;
                if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, directory_index.children[i], 1, (void *) &file_node)) {
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

    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, file, 1, (void *) &directory_node)) {
        return false;
    }
    uint16_t i;
    for (i = 0; i < FILESYSTEM_NAME_MAX_SIZE && directory_node.name[i] != '\0'; i++) buffer[i] = directory_node.name[i];
    buffer[i] = '\0';

    return true;
}
bool get_file_name(file_t file, char * buffer) {
    filesystem_file_node_page_t file_node;

    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, file, 1, (void *) &file_node)) {
        return false;
    }
    uint16_t i;
    for (i = 0; i < FILESYSTEM_NAME_MAX_SIZE && file_node.name[i] != '\0'; i++) buffer[i] = file_node.name[i];
    buffer[i] = '\0';

    return true;
}

bool directory_iterator_init(directory_iterator_t * iterator, directory_t directory) {
    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, directory, 1, (void *) &iterator->node_page)) {
        return false;
    }
    if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, iterator->node_page.directory_index_address, 1, (void *) &iterator->index_page)) {
        return false;
    }

    iterator->index_location = 0;

    return true;
}

filesystem_directory_entry_type_t directory_iterator_next(directory_iterator_t * iterator, filesystem_page_address_t * handle) {
    if (iterator->index_location >= FILESYSTEM_DIRECTORY_INDEX_CHILDREN_SIZE) {
        if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, iterator->index_page.next_index_address, 1, (void *) &iterator->index_page)) {
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

        if (disc_read48(ATA_PIO_PRIMARY, DISC_READ48_MASTER, *handle, 1, (void *) &page)) {
            return FS_DET_NONE;
        }

        switch (page.type) {
            case FILESYSTEM_PAGE_TYPE_FILE: return FS_DET_FILE;
            case FILESYSTEM_PAGE_TYPE_DIRECTORY: return FS_DET_DIRECTORY;
            default: return FS_DET_NONE;
        }
    }
}