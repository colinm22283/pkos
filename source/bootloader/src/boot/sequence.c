#include <boot/sequence.h>
#include <boot/disc.h>

#include <console/print.h>
#include <console/print_bool.h>
#include <console/newline.h>

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

uint32_t boot_sequence_start() {
    print_init("disc");
    if (!boot_disc_init()) return 1;
    print_done();
    console_print("Disc info:\n  Primary");
    console_print(" drive found: ");
    console_print_bool(boot_disc_primary_present);
    console_print("\n  Secondary");
    console_print(" drive found: ");
    console_print_bool(boot_disc_secondary_present);
    console_print("\n  Disc selected: ");
    console_print(boot_disc_master_selected ? "MASTER\n" : "SLAVE\n");

    print_init("64bit gdt");
    gdt64_init();
    print_done();

    print_init("paging tables");
    page_tables_init();
    print_done();

    return 1;
}