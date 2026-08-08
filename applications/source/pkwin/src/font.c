#include <font.h>
#include <bmp.h>

image_t font;

void font_init(void) {
    bmp_load(&font, "/etc/pkwin/font.bmp");
}

