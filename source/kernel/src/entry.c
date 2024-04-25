#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/video_bios.h>

#include <paging/map_kernel.h>
#include <paging/allocator.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <util/string/strcpy.h>

#include <filesystem/filesystem.h>

typedef struct { int32_t x; int32_t y; } point_t;

__NORETURN void kernel_entry_error(uint32_t error_code);

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    driver_video_bios_load(&driver_table);
    driver_table.video.start();

    paging_map_kernel();
    if (!page_allocator_init()) {
        kernel_entry_error(1);
    }

//    uint16_t device_count = driver_table.disc.device_count();
    driver_table.disc.select_device(0);

    driver_table_video_mode_t * video_modes = driver_table.video.get_modes();
//    uint32_t video_modes_count = driver_table.video.mode_count();
    driver_table.video.set_mode(0);

    uint8_t color = 2;
    driver_table.video.set_color(&color);

    driver_table.video.fill_rect(0, 0, video_modes[0].width, video_modes[0].height);

    uint8_t smile[] = {
        0b00000000,
        0b01000100,
        0b01000100,
        0b00000000,
        0b10000001,
        0b01000010,
        0b00111100,
        0b00000000,
    };

    color = 5;
    for (int i = 0; i < video_modes[0].width; i += 8) {
        for (int j = 0; j < video_modes[0].height; j += 8) {
            driver_table.video.set_color(&color);
            driver_table.video.draw_bitmap_transparent(smile, i, j, 8, 8);

            color++;
        }
    }

    driver_table.disc.stop();
    driver_table.video.stop();

    halt();
}

const uint8_t kernel_error_num_font[][8] = {
    {
        0b01111100,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b01111100,
        0b00000000,
    }, {
        0b00010000,
        0b00110000,
        0b01010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b11111110,
        0b00000000,
    }, {
        0b01111100,
        0b10000010,
        0b00000010,
        0b00001100,
        0b00110000,
        0b01000000,
        0b11111110,
        0b00000000,
    }, {
        0b01111100,
        0b10000010,
        0b00000010,
        0b01111100,
        0b00000010,
        0b10000010,
        0b01111100,
        0b00000000,
    }, {
        0b00001000,
        0b00011000,
        0b00101000,
        0b01001000,
        0b11111110,
        0b00001000,
        0b00001000,
        0b00000000,
    }, {
        0b11111110,
        0b10000000,
        0b10000000,
        0b11111100,
        0b00000010,
        0b10000010,
        0b01111100,
        0b00000000,
    }, {
        0b01111100,
        0b10000000,
        0b10000000,
        0b11111100,
        0b10000010,
        0b10000010,
        0b01111100,
        0b00000000,
    }, {
        0b11111110,
        0b00000100,
        0b00000100,
        0b00001000,
        0b00001000,
        0b00010000,
        0b00010000,
        0b00000000,
    }, {
        0b01111100,
        0b10000010,
        0b10000010,
        0b01111100,
        0b10000010,
        0b10000010,
        0b01111100,
        0b00000000,
    }, {
        0b01111100,
        0b10000010,
        0b10000010,
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111100,
        0b00000000,
    },
};

__NORETURN void kernel_entry_error(uint32_t error_code) {
    uint8_t color = 1;
    driver_table.video.set_color(&color);

    const driver_table_video_mode_t * video_mode = driver_table.video.get_mode();

    driver_table.video.fill_rect(0, 0, video_mode->width, video_mode->height);

    color = 15;
    driver_table.video.set_color(&color);

    for (int i = 7 * 8; i >= 0; i -= 8) {
        uint8_t num = error_code % 16;
        error_code /= 16;

        driver_table.video.draw_bitmap_transparent(kernel_error_num_font[num], i, 0, 8, 8);
    }

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