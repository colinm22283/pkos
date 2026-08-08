#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <render.h>
#include <state.h>
#include <mouse.h>
#include <config.h>
#include <cursor.h>
#include <image.h>
#include <font.h>

uint8_t * fb;

uint8_t prep_fb[HEIGHT * WIDTH];

void draw_font(char c, int ix, int iy) {
    int ox = ((c - 32) % 32) * 6;
    int oy = ((c - 32) / 32) * 9;

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 8; y++) {
            int sx = ix + x;
            int sy = iy + y;

            if (sx < 0 || sx >= WIDTH || sy < 0 || sy >= HEIGHT) continue;

            if (font.pixels[(oy + y) * font.w + (ox + x)] != 16) {
                prep_fb[sy * WIDTH + sx] = 16;
            }
        }
    }
}

void draw_image(image_t * image, int ix, int iy) {
    for (int x = 0; x < image->w; x++) {
        for (int y = 0; y < image->h; y++) {
            int sx = ix + x;
            int sy = iy + y;

            if (sx < 0 || sx >= WIDTH || sy < 0 || sy >= HEIGHT) continue;

            if (image->pixels[y * image->w + x] != 31) {
                prep_fb[sy * WIDTH + sx] = image->pixels[y * image->w + x];
            }
        }
    }
}

void draw_bar(const char * name, int wx, int wy, int w) {
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < bar_height; y++) {
            int sx = wx + x;
            int sy = wy + y - bar_height;

            if (sx < 0 || sx >= WIDTH || sy < 0 || sy >= HEIGHT) continue;

            prep_fb[sy * WIDTH + sx] = 24;
        }
    }

    for (int i = 0; name[i] != '\0'; i++) {
        draw_font(name[i], wx + 5 * i, wy - bar_height);
    }
}

void draw_window(window_t * window) {
    for (int x = 0; x < window->w; x++) {
        for (int y = 0; y < window->h; y++) {
            int sx = window->x + x;
            int sy = window->y + y;

            if (sx < 0 || sx >= WIDTH || sy < 0 || sy >= HEIGHT) continue;

            prep_fb[sy * WIDTH + sx] = window->fb[y * window->w + x];
        }
    }
    draw_bar(window->title, window->x, window->y, window->w);
}

void render(void) {
    acquire(&window_lock);

    for (size_t x = 0; x < WIDTH; x++) {
        for (size_t y = 0; y < HEIGHT; y++) {
            prep_fb[y * WIDTH + x] = 3;
        }
    }

    for (size_t i = 0; i < window_count; i++) {
        window_t * window = windows[i];

        draw_window(window);
    }

    mouse_coord_t mouse = get_mouse_pos();

    if (held_window == NULL) draw_image(&cursor, mouse.x, mouse.y);

    for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
        fb[i] = prep_fb[i];
    }

    release(&window_lock);
}

__attribute__((noreturn)) void render_loop(void) {
    int fb_fd = open("/dev/vga", O_RDWR);
    fb = map(fb_fd, NULL, WIDTH * HEIGHT, 0, MAP_WRITE);

    while (true) {
        if (held_window != NULL) {
            mouse_coord_t coord = get_mouse_pos();

            held_window->x = coord.x;
            held_window->y = coord.y;
        }

        render();

        nanosleep(16666666 / 10);
    }
}

