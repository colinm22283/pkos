#include <stddef.h>

#include <driver/driver_vector_table.h>

#include <main.h>
#include <rect.h>
#include <modes.h>
#include <bitmap.h>
#include <image.h>
#include <pixel.h>

#include <defs.h>

uint64_t allocation_size(void) {
    return sizeof(allocation_t);
}

bool unload(void * _allocation, void * _driver_table) {
    driver_table_t * driver_table = _driver_table;

    driver_table->video.allocation = NULL;

    driver_table->video.unload = NULL;

    driver_table->video.mode_count = NULL;
    driver_table->video.get_modes = NULL;
    driver_table->video.set_mode = NULL;
    driver_table->video.get_mode = NULL;
    driver_table->video.set_color = NULL;

    driver_table->video.draw_rect = NULL;
    driver_table->video.fill_rect = NULL;

    driver_table->video.draw_image = NULL;

    driver_table->video.draw_bitmap = NULL;
    driver_table->video.draw_bitmap_transparent = NULL;

    return true;
}

bool load(void * load_address, void * _allocation, driver_table_t * driver_table) {
    allocation_t * allocation = _allocation;

    allocation->driver_modes[0].width = 320;
    allocation->driver_modes[0].height = 200;
    allocation->driver_modes[0].color_mode = DRIVER_TABLE_VIDEO_MODE_COLOR_MODE_256_COLOR;

    allocation->current_color = 0;

    driver_table->video.allocation = _allocation;

    driver_table->video.unload = unload + (intptr_t) load_address;

    driver_table->video.mode_count = mode_count + (intptr_t) load_address;
    driver_table->video.get_modes = get_modes + (intptr_t) load_address;
    driver_table->video.set_mode = set_mode + (intptr_t) load_address;
    driver_table->video.get_mode = get_mode + (intptr_t) load_address;
    driver_table->video.set_color = set_color + (intptr_t) load_address;

    driver_table->video.draw_pixel = draw_pixel + (intptr_t) load_address;

    driver_table->video.draw_rect = draw_rect + (intptr_t) load_address;
    driver_table->video.fill_rect = fill_rect + (intptr_t) load_address;

    driver_table->video.draw_image = draw_image + (intptr_t) load_address;

    driver_table->video.draw_bitmap = draw_bitmap + (intptr_t) load_address;
    driver_table->video.draw_bitmap_transparent = draw_bitmap_transparent + (intptr_t) load_address;
}

__SECTION(".driver_vector_table") driver_vector_table_t driver_vector_table = {
    .allocation_size = allocation_size,
    .load = load,
};