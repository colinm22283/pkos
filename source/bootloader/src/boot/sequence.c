#include <boot/sequence.h>
#include <boot/disc.h>
#include <boot/enter_kernel.h>
#include <boot/kernel.h>
#include <boot/config.h>
#include <boot/graphics_mode.h>

#include <disc/read.h>

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

    print_init("kernel memory");
    if (!boot_disc_load_kernel()) return 2;
    print_done();

    print_init("paging tables");
    page_tables_init();
    print_done();

    print_init("BIOS graphics mode");
    boot_switch_graphics_mode();
    print_done();

    bool boot_result;
#ifdef BOOT_CONFIG_64_BIT_ENABLE
    boot_result = enter_kernel64();
#else
    boot_result = enter_kernel32();
#endif

    if (!boot_result) return 3;

    return 0;
}