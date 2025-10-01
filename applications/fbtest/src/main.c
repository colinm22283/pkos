#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

int main(uint64_t argc, const char ** argv) {
    fd_t bind_fd = open("/sys/vgatty/bind", OPEN_WRITE);
    write(bind_fd, "0", 1);

    fd_t fb_fd = open("/dev/vga", OPEN_WRITE | OPEN_READ);
    uint8_t * framebuffer = map(fb_fd, NULL, 320 * 200 + 10, 0, MAP_WRITE);

    for (int i = 0; i < 320 * 200; i++) {
        framebuffer[i] = 3;
    }

    int x = 5, y = 10;
    int vx = 1, vy = 2;

    for (uint64_t j = 0; j < 1000; j++) {
        framebuffer[y * 320 + x] = 0;

        x += vx;
        y += vy;

        if (x < 0) {
            vx *= -1;
            x = 0;
        }
        
        if (x >= 320) {
            vx *= -1;
            x == 319;
        }

        if (y < 0) {
            vy *= -1;
            y = 0;
        }
        
        if (y >= 200) {
            vy *= -1;
            y == 199;
        }

        for (uint64_t i = 0; i < 1000000; i++) asm volatile("nop");
    }

    close(fb_fd);

    write(bind_fd, "1", 1);
    close(bind_fd);

    return 0;
}
