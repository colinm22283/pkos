#include <module/info_table.h>

#include <defs.h>

#include <filesystem/filesystem.h>

#define VIDEO_MEMORY ((uint8_t *) 0xA0000)

__ALWAYS_INLINE static inline void draw_bitmap(const void * _bitmap, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    const uint8_t * bitmap = _bitmap;

    uint8_t color = 1;

    uint32_t div_width = w / 8;

    uint32_t video_width = 320;

    for (uint32_t _x = 0, __x = 0; _x < w; _x += 8, __x++) {
        for (uint32_t _y = 0; _y < h; _y++) {
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 0)] = (bitmap[_y * div_width + __x] >> 7) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 1)] = (bitmap[_y * div_width + __x] >> 6) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 2)] = (bitmap[_y * div_width + __x] >> 5) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 3)] = (bitmap[_y * div_width + __x] >> 4) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 4)] = (bitmap[_y * div_width + __x] >> 3) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 5)] = (bitmap[_y * div_width + __x] >> 2) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 6)] = (bitmap[_y * div_width + __x] >> 1) & 1 ? color : 0;
            VIDEO_MEMORY[(y + _y) * video_width + (x + _x + 7)] = (bitmap[_y * div_width + __x] >> 0) & 1 ? color : 0;
        }
    }
}

bool init(module_info_table_t * info_table) {
    VIDEO_MEMORY[0] = 1;

    char bitmap[256] = { 0b10101010, 0b01010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101, 0b10101010, 0b01010101 };

//    file_reader_t file_reader;
//    file_reader_init(&file_reader, open_file_path(open_filesystem(FILESYSTEM_ROOT_ADDRESS), "home/smile.bmp"));
//    file_reader_read(&file_reader, bitmap, 256);

    draw_bitmap(bitmap, 10, 10, 8, 8);

    return true;
}

bool free(module_info_table_t * info_table) {
    return true;
}

DEFINE_MODULE_INFO_TABLE("hello_world");