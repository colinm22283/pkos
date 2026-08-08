#include <cursor.h>
#include <bmp.h>

image_t cursor;

void cursor_init(void) {
    bmp_load(&cursor, "/etc/pkwin/cursor.bmp");
}

