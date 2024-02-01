#include <commands/boot.h>

#include <console/print.h>

#include <gdt64.h>
#include <page_tables.h>

static inline void print_init(const char * message) {
    console_print("Init ");
    console_print(message);
    console_print("...\n");
}

__CDECL uint32_t command_boot(uint32_t argc, const char ** argv) {
    console_print("Beginning boot sequence...\n");

    print_init("64bit gdt");
    gdt64_init();

    print_init("paging tables");
    page_tables_init();

    return 1;
}