#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/driver_interface.h>
#include <driver/driver_vector_table.h>
#include <driver/driver.h>

#include <paging/map_kernel.h>
#include <paging/allocator.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <util/string/strcpy.h>

#include <filesystem/filesystem.h>

#include <entry_error.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    paging_map_kernel();
    if (!page_allocator_init()) {
        kernel_entry_error(1);
    }

//    uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

    driver_handle_t handle;
    if (!load_driver(&handle, "boot/driver/disc_pio.drv")) halt();

    driver_video_set_mode(0);

    uint8_t color = 1;
    driver_video_set_color(&color);

    driver_video_fill_rect(10, 10, 50, 50);

    uint8_t smile[] = {
        0b00000000,
        0b01000100,
        0b01000100,
        0b00000000,
        0b10000010,
        0b01000100,
        0b00111000,
        0b00000000,
    };

    color = 2;
    driver_video_set_color(&color);
    driver_video_draw_bitmap_transparent(smile, 20, 20, 8, 8);

    driver_table.disc.stop();

    halt();
}