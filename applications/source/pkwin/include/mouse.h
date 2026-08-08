#pragma once

typedef struct {
    int x, y;
} mouse_coord_t;

void mouse_init(void);
mouse_coord_t get_mouse_pos(void);

