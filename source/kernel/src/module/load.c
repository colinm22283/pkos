#include <stddef.h>

#include <module/load.h>

char memory[4096];

module_info_table_t * module_load(directory_t dir, const char * path) {
    file_t file = open_file_path(dir, path);

    file_reader_t file_reader;
    file_reader_init(&file_reader, file);
    uint32_t size = file_reader_read(&file_reader, memory, 4096);

    module_info_table_t * info_table = (module_info_table_t *) memory;

    info_table->init = info_table->init + (intptr_t) memory;
    info_table->free = info_table->free + (intptr_t) memory;

    return info_table;
}