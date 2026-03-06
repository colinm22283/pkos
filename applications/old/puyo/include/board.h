#pragma once

#define BUFFER_WIDTH  (320)
#define BUFFER_HEIGHT (200)

#define BOARD_WIDTH   (10)
#define BOARD_HEIGHT  (30)

#define TILE_SIZE     (5)

#define BOARD_YPOS    ((BUFFER_HEIGHT - (BOARD_HEIGHT * TILE_SIZE)) / 2)
#define BOARD_XPOS    ((BUFFER_WIDTH - (BOARD_WIDTH * TILE_SIZE)) / 2)

typedef struct {
    uint8_t color;
} tile_t;

extern tile_t board[BOARD_HEIGHT][BOARD_WIDTH];

void board_init(void);
void board_free(void);

void board_draw(void);
