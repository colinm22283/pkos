#include <modes.h>
#include <main.h>

uint32_t mode_count(void * allocation) {
    return MODE_COUNT;
}
const driver_table_video_mode_t * get_modes(void * _allocation) {
    allocation_t * allocation = _allocation;

    return allocation->driver_modes;
}
bool set_mode(void * allocation, uint32_t mode_index) {
    if (mode_index >= MODE_COUNT) return false;

    return true;
}
const driver_table_video_mode_t * get_mode(void * _allocation) {
    allocation_t * allocation = _allocation;

    return &allocation->driver_modes[0];
}

bool set_color(void * _allocation, const void * color) {
    allocation_t * allocation = _allocation;
    allocation->current_color = *(uint8_t *) color;

    return true;
}