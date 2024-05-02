#include <entry_error.h>

#include <driver_table/driver_table.h>

#include <sys/halt.h>

const uint8_t kernel_error_font_nums[][8] = {
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
const uint8_t kernel_error_font_x[8] = {
    0b10000010,
    0b01000100,
    0b00101000,
    0b00010000,
    0b00101000,
    0b01000100,
    0b10000010,
    0b00000000,
};

__NORETURN void kernel_entry_error(uint32_t error_code) {
    uint8_t color = 1;
    driver_table.video.set_color(&color);

    const driver_table_video_mode_t * video_mode = driver_table.video.get_mode();

    driver_table.video.fill_rect(0, 0, video_mode->width, video_mode->height);

    color = 15;
    driver_table.video.set_color(&color);

    driver_table.video.draw_bitmap_transparent(kernel_error_font_nums[0], 0, 0, 8, 8);
    driver_table.video.draw_bitmap_transparent(kernel_error_font_x, 8, 0, 8, 8);

    for (int i = 7 * 8; i >= 0; i -= 8) {
        uint8_t num = error_code % 16;
        error_code /= 16;

        driver_table.video.draw_bitmap_transparent(kernel_error_font_nums[num], 16 + i, 0, 8, 8);
    }

    halt();
}