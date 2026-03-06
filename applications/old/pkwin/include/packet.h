#pragma once

#include <defs.h>

#include <window.h>

enum {
    PKW_STAT,
    PKW_CMD_CREATE_WIN,
    PKW_CMD_MOVE_WIN,
};

enum {
    PKW_STAT_OK,
    PKW_STAT_INV_CMD,
};

typedef struct __PACKED {
    uint16_t window_id;
    uint8_t command;
    uint32_t size;
} pkw_cmd_header_t;

typedef struct __PACKED {
    pkw_cmd_header_t header;

    uint16_t status;
} pkw_stat_t;

typedef struct __PACKED {
    pkw_cmd_header_t header;

    char title[TITLE_MAX];
} pkw_cmd_create_win_t;

typedef struct __PACKED {
    pkw_cmd_header_t header;

    uint32_t x, y;
} pkw_cmd_move_win_t;

pkw_cmd_header_t * receive_command(fd_t sock_fd);
void send_status(fd_t sock_fd, uint16_t status);
