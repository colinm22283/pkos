#include <stdint.h>
#include <stdbool.h>

#include <defs.h>

#include <bios_console.h>

#include <memory_manager/mm_init.h>

#include <interrupt/init.h>
#include <interrupt/interrupt.h>
#include <interrupt/pic.h>

#include <paging/paging.h>

#include <string/strcpy.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry(void) {
    print_string("Init Starting...\n");

    // clear memory identity mapping
    print_string("Clearing Identity Map... ");
//    paging_clear_identity_map();
    print_string_color("DONE\n", BIOS_COLOR(BC_GREEN, BC_BLACK));

    // configure interrupts
    print_string("Init Interrupts... ");
    //interrupt_init();
    print_string_color("DONE\n", BIOS_COLOR(BC_GREEN, BC_BLACK));

    // disable the pic
    print_string("Remapping PIC... ");
    //pic_remap(0x20, 0x28);
    //pic_mask_all();
    print_string_color("DONE\n", BIOS_COLOR(BC_GREEN, BC_BLACK));

    // enable the apic

    // initialize the memory manager
    print_string("Initializing Memory Manager... ");
    //mm_init();
    print_string_color("DONE\n", BIOS_COLOR(BC_GREEN, BC_BLACK));

    print_string("Init complete\n");

    print_string("<Start main process>\n");

    while (true) wait_for_interrupt();
}