#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>

#include <bmp.h>

typedef struct __attribute__((packed)) {
    char sig[2];
    uint32_t size;
    uint16_t res0;
    uint16_t res1;
    uint32_t data_offset;
} bmp_header_t;

typedef struct __attribute__((packed)) {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t color_planes;
    uint16_t bpp;
    uint32_t compression;
} bmp_info_header_t;

int bmp_load(image_t * image, const char * path) {
    FILE * file = fopen(path, "r");

    bmp_header_t header;
    fread(&header, 1, sizeof(bmp_header_t), file);

    bmp_info_header_t info;
    fread(&info, 1, sizeof(bmp_info_header_t), file);

    image->w = info.width;
    image->h = info.height;
    /* image->pixels = malloc(image->w * image->h); */

    fseek(file, header.data_offset, SEEK_SET);

    size_t offset = 0;
    for (int y = 0; y < image->h; y++) {
        uint8_t row[3 * image->w];
        fread(row, 1, 3 * image->w, file);

        for (int x = 0; x < image->w; x++) {
            image->pixels[(image->h - y - 1) * image->w + x] = 16 + row[x * 3] / 16;

            offset += 3;
        }

        fseek(file, 4 - offset % 4, SEEK_CUR);
        offset = 0;
    }

    fclose(file);
}

