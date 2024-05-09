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
    if (!load_driver(&handle, "boot/driver/video_bios.drv")) halt();

    driver_video_set_mode(0);

    uint8_t color = 1;
    driver_video_set_color(&color);

    driver_video_fill_rect(10, 10, 50, 50);

    uint8_t smile[8];
    file_t smile_file = open_file_path(open_filesystem(FILESYSTEM_ROOT_ADDRESS), "home/smile.bmp");
    file_reader_t reader;
    file_reader_init(&reader, smile_file);
    file_reader_read(&reader, (char *) smile, 8);

    color = 2;
    driver_video_set_color(&color);
    driver_video_draw_bitmap_transparent(smile, 20, 20, 8, 8);

    driver_table.disc.stop();

    halt();
}