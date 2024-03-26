#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/video_bios.h>

#include <paging/map_kernel.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <util/string/strcpy.h>

#include <filesystem/filesystem.h>

typedef struct { int32_t x; int32_t y; } point_t;

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    paging_map_kernel();

    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    driver_video_bios_load(&driver_table);
    driver_table.video.start();

//    __MAYBE_UNUSED uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

//    __MAYBE_UNUSED driver_table_video_mode_t * video_modes = driver_table.video.get_modes();
//    __MAYBE_UNUSED uint32_t video_modes_count = driver_table.video.mode_count();
    driver_table.video.set_mode(0);

    uint8_t color = 1;
    driver_table.video.set_color(&color);

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            driver_table.video.draw_pixel(i, j);
        }
    }

    driver_table.disc.stop();
    driver_table.video.stop();

    halt();
}

__SECTION(".filesystem") struct {
    filesystem_root_page_t root_page;
    filesystem_directory_node_page_t root_directory;
} filesystem = {
    .root_page = {
        .tag = { .in_use = true, },
        .signature = FILESYSTEM_ROOT_SIGNATURE,
    },
    .root_directory = {

    },
};