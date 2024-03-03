#include <stdint.h>

#include <defs.h>

#include <sys/halt.h>

#include <driver/disc_pio.h>
#include <driver/video_bios.h>
#include <driver/terminal.h>

__NORETURN __SECTION(".kernel_entry") void kernel_entry() {
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
            uint8_t color = 1;
            driver_table.video.set_color(&color);
        }
        for (uint32_t x = 0; x < video_modes[0].width / 2; x++) {
            driver_table.video.draw_pixel(x, y);
        }
        {
            uint8_t color = 5;
            driver_table.video.set_color(&color);
        }
        for (uint32_t x = video_modes[0].width / 2; x < video_modes[0].width; x++) {
            driver_table.video.draw_pixel(x, y);
        }
    }

    uint8_t bmp[8][2] = {
        { 0b10101010, 0b10101010 },
        { 0b01010101, 0b01010101 },
        { 0b10101010, 0b10101010 },
        { 0b01010101, 0b01010101 },
        { 0b10101010, 0b10101010 },
        { 0b01010101, 0b01010101 },
        { 0b10101010, 0b10101010 },
        { 0b01010101, 0b01010101 },
    };

    driver_table.video.draw_bitmap((void *) bmp, 200, 200, 16, 8);

    driver_table.disc.read(0, 40, (void *) 0xA0000);

    driver_table.disc.stop();
    driver_table.video.stop();

    halt();
}