#include <stddef.h>

#include <defs.h>

#include <driver/driver_table.h>

#include <module/entry_table.h>

#include <modules/video_bios/main.h>
#include <modules/video_bios/rect.h>
#include <modules/video_bios/modes.h>
#include <modules/video_bios/bitmap.h>
#include <modules/video_bios/image.h>
#include <modules/video_bios/pixel.h>

uint64_t allocation_size(void) {
    return sizeof(allocation_t);
}

bool free(void) {
    driver_table.video.allocation = NULL;

    driver_table.video.unload = NULL;

    driver_table.video.mode_count = NULL;
    driver_table.video.get_modes = NULL;
    driver_table.video.set_mode = NULL;
    driver_table.video.get_mode = NULL;
    driver_table.video.set_color = NULL;

    driver_table.video.draw_rect = NULL;
    driver_table.video.fill_rect = NULL;

    driver_table.video.draw_image = NULL;

    driver_table.video.draw_bitmap = NULL;
    driver_table.video.draw_bitmap_transparent = NULL;

    return true;
}

bool init(void * load_address) {
    allocation->driver_modes[0].width = 320;
    allocation->driver_modes[0].height = 200;
    allocation->driver_modes[0].color_mode = DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_256_COLOR;

    allocation->current_color = 0;

    driver_table.video.unload = unload + (intptr_t) load_address;

    driver_table.video.mode_count = mode_count + (intptr_t) load_address;
    driver_table.video.get_modes = get_modes + (intptr_t) load_address;
    driver_table.video.set_mode = set_mode + (intptr_t) load_address;
    driver_table.video.get_mode = get_mode + (intptr_t) load_address;
    driver_table.video.set_color = set_color + (intptr_t) load_address;

    driver_table.video.draw_pixel = draw_pixel + (intptr_t) load_address;

    driver_table.video.draw_rect = draw_rect + (intptr_t) load_address;
    driver_table.video.fill_rect = fill_rect + (intptr_t) load_address;

    driver_table.video.draw_image = draw_image + (intptr_t) load_address;

    driver_table.video.draw_bitmap = draw_bitmap + (intptr_t) load_address;
    driver_table.video.draw_bitmap_transparent = draw_bitmap_transparent + (intptr_t) load_address;
}

module_entry_table_t module_entry_table = {
    .init = init,
    .free = free,
};