#include <stddef.h>

#include <filesystem/directory_locate.h>

#include <driver_table/driver_table.h>

#include <util/string/strcmp.h>
#include <util/memory/memcpy.h>

bool filesystem_directory_locate(filesystem_directory_page_t * directory, const char * name, void * result_page) {
    filesystem_directory_index_page_t current_index;
    if (!driver_table.disc.read(directory->index_address, 1, &current_index)) return false;

    while (true) {
        for (int i = 0; i < 126; i++) {
            filesystem_page_address_t child_address = current_index.children[i];

            if (child_address == 0) return false;

            union { filesystem_directory_page_t directory; filesystem_file_page_t file; } found_page;
            if (!driver_table.disc.read(child_address, 1, &found_page)) return false;

            if (found_page.directory.signature == FILESYSTEM_SIGNATURE_DIRECTORY) {
                if (strcmp(found_page.directory.name, name) == 0) {
                    if (result_page != NULL) *(filesystem_directory_page_t *) result_page = found_page.directory;

                    return true;
                }
            }
            else if (found_page.file.signature == FILESYSTEM_SIGNATURE_FILE) {
                if (strcmp(found_page.file.name, name) == 0) {
                    if (result_page != NULL) *(filesystem_file_page_t *) result_page = found_page.file;

                    return true;
                }
            }
            else return false;
        }

        if (current_index.next != 0) {
            if (!driver_table.disc.read(current_index.next, 1, &current_index)) return false;
        }
        else return false;
    }
}