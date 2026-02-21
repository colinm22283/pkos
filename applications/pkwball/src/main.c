#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

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

    char title[100];
} pkw_cmd_create_win_t;

typedef struct __PACKED {
    pkw_cmd_header_t header;

    uint32_t x, y;
} pkw_cmd_move_win_t;

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

void strcpy(char * dst, const char * src) {
    uint64_t i = 0;
    do {
        dst[i] = src[i];
        i++;
    }
    while (src[i] != '\0');
    dst[i] = src[i];
}

uint64_t strlen(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;
    return str_size;
}

int main(uint64_t argc, const char ** argv) {
    print("Start pkwball\n");

    fd_t sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);

    while (true) {
        char addr_buffer[512];
        sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
        strcpy(sockaddr->path, "/tmp/pkw.sock");

        if (connect(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1) == ERROR_OK) break;
    }

    print("create window\n");

    pkw_cmd_create_win_t create_win_message = {
        .header = {
            .command = PKW_CMD_CREATE_WIN,
            .size = sizeof(pkw_cmd_create_win_t),
            .window_id = 0,
        },
        .title = "test win\0",
    };

    write(sock_fd, (char *) &create_win_message, sizeof(pkw_cmd_create_win_t));

    while (true) { }
}
