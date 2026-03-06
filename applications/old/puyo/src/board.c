#include <pkos.h>

#include <board.h>

uint8_t * fb;

tile_t board[BOARD_HEIGHT][BOARD_WIDTH];

void board_init(void) {
    for (size_t i = 0; i < BOARD_HEIGHT; i++) {
        for (size_t j = 0; j < BOARD_WIDTH; j++) {
            board[i][j].color = 0;
        }
    }

    fd_t bind_fd = open("/sys/vgatty/bind", OPEN_WRITE);
    write(bind_fd, "0", 1);
    close(bind_fd);

    fd_t fb_fd = open("/dev/vga", OPEN_WRITE | OPEN_READ);
    fb = map(fb_fd, NULL, BUFFER_WIDTH * BUFFER_HEIGHT, 0, MAP_WRITE);
}

void board_free(void) {
    fd_t bind_fd = open("/sys/vgatty/bind", OPEN_WRITE);
    write(bind_fd, "1", 1);
    close(bind_fd);
}

void board_draw(void) {
    for (size_t i = 0; i < BOARD_HEIGHT; i++) {
        for (size_t j = 0; j < BOARD_WIDTH; j++) {
            uint8_t color = board[i][j].color;

            for (size_t i0 = 0; i0 < TILE_SIZE; i0++) {
                for (size_t j0 = 0; j0 < TILE_SIZE; j0++) {
                    size_t y = BOARD_YPOS + i * TILE_SIZE + i0;
                    size_t x = BOARD_XPOS + j * TILE_SIZE + j0;

                    fb[y * BUFFER_WIDTH + x] = color;
                }
            }
        }
    }
}
