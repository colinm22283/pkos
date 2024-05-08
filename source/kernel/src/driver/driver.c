#include <driver/driver.h>

#include <filesystem/filesystem.h>

#include <driver/driver_vector_table.h>
#include <driver/driver_interface.h>

static char data[4000];
static char driver_allocation[1000];

bool load_driver(driver_handle_t * handle, const char * path) {
    file_t file = open_file_path(open_filesystem(FILESYSTEM_ROOT_ADDRESS), path);

    if (file == 0) return false;

    file_reader_t reader;
    file_reader_init(&reader, file);
    file_reader_read(&reader, data, 4000);

    driver_vector_table_t * vector_table = (driver_vector_table_t *) &data;

    return (vector_table->load + (intptr_t) data)(data, driver_allocation, &driver_table);
}