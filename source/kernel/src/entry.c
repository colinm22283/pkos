#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>

#include <memory/map_kernel.h>
#include <memory/memory_map.h>

#include <paging/allocator.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <util/string/strcpy.h>

#include <filesystem/filesystem.h>

#include <interrupt/init.h>

#include <entry_error.h>

#include <module/info_table.h>
#include <module/load.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    driver_disc_pio_load(&driver_table);
    if (!driver_table.disc.start()) kernel_entry_error(1);

    paging_map_kernel();

//    int_init();

    if (!page_allocator_init()) kernel_entry_error(0x2);

//    kernel_entry_error(0x123456);

//    uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

#define VIDEO_MEMORY ((uint8_t *) 0xA0000)

    VIDEO_MEMORY[0] = 3;
    VIDEO_MEMORY[1] = 3;
    VIDEO_MEMORY[2] = 3;

//    module_info_table_t * hello_world_entry_table = module_load(open_filesystem(FILESYSTEM_ROOT_ADDRESS), "boot/module/hello_world.mod");

//    hello_world_entry_table->init(hello_world_entry_table);

    driver_table.disc.stop();

    halt();
}