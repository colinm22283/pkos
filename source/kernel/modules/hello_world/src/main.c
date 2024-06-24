#include <module/entry_table.h>

#include <defs.h>

bool init(void * allocation_root) {
    return true;
}

bool free(void) {
    return true;
}

__SECTION(".entry_table") module_entry_table_t entry_table = {
    .init = init,
    .free = free,
};