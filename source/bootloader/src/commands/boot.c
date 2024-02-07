#include <commands/boot.h>

#include <console/print.h>

#include <gdt64.h>
#include <page_tables.h>

static inline void print_init(const char * message) {
    console_print("Init ");
    console_print(message);
    console_print("... ");
}

static inline void print_done() {
    console_print("done!\n");
}

__CDECL uint32_t command_boot(uint32_t argc, const char ** argv) {
    console_print("Beginning boot sequence...\n");

    print_init("file system");
    print_done();

    print_init("64bit gdt");
    gdt64_init();
    print_done();

    print_init("paging tables");
    page_tables_init();
    print_done();

    return 1;
}