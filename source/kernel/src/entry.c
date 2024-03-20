#include <entry.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/video_bios.h>

#include <paging/map_kernel.h>

#include <stack.h>

#include <sys/stack/load_stack_pointer.h>

#include <sys/asm/nop.h>

typedef struct { int32_t x; int32_t y; } point_t;

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
    load_stack_pointer(stack_top);

    paging_map_kernel();

    driver_disc_pio_load(&driver_table);
    driver_table.disc.start();

    driver_video_bios_load(&driver_table);
    driver_table.video.start();

    uint16_t device_count = driver_table.disc.device_count();

    driver_table.disc.select_device(0);

    driver_table_video_mode_t * video_modes = driver_table.video.get_modes();
    uint32_t video_modes_count = driver_table.video.mode_count();

    driver_table.video.set_mode(0);

    for (uint32_t y = 0; y < video_modes[0].height; y++) {
        {
            uint8_t color = 0;
            driver_table.video.set_color(&color);
        }
        for (uint32_t x = 0; x < video_modes[0].width; x++) {
            driver_table.video.draw_pixel(x, y);
        }
    }

    uint8_t bmp[2 * 8] = {
        0b10101010, 0b10101010,
        0b01010101, 0b01010101,
        0b10101010, 0b10101010,
        0b01010101, 0b01010101,
        0b10101010, 0b10101010,
        0b01010101, 0b01010101,
        0b10101010, 0b10101010,
        0b01010101, 0b01010101,
    };

    driver_table.disc.read(0, 40, (void *) 0xA0000);

    {
        uint8_t color = 0xF;
        driver_table.video.set_color(&color);
    }
    driver_table.video.draw_bitmap_transparent((void *) bmp, 100, 100, 16, 8);

    driver_table.disc.stop();
    driver_table.video.stop();

    halt();
}