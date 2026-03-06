#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <packet.h>

#include <packet.h>

#define WIDTH (320)
#define HEIGHT (200)
uint8_t * fb;

typedef struct {
    int x, y, w, h;
} window_t;

size_t window_count;
window_t * windows;

int main(int argc, const char ** argv) {
    int fb_fd = open("/dev/vga", O_RDWR);
    fb = map(fb_fd, NULL, WIDTH * HEIGHT, 0, MAP_WRITE);

    window_count = 0;
    windows = malloc(1);

    printf("Open socket\n");
    int sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (sock_fd < 0) {
        printf("Error opening server socket: %s\n", strerrordesc_np(-sock_fd));
        return 1;
    }

    char addr_buffer[512];
    sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
    strcpy(sockaddr->path, "/tmp/pkw.sock");

    printf("connect()\n");

    int result;

    result = connect(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1);
    if (result < 0) {
        printf("Unable to connect to /tmp/pkw.sock: %s\n", strerrordesc_np(-result));
    }

    pkw_cmd_create_win_t packet = {
        .header = {
            .command = PKW_CMD_CREATE_WIN,
            .size = sizeof(pkw_cmd_create_win_t),
            .window_id = 0,
        },
    };

    strcpy(packet.title, "pkwball");

    write(sock_fd, (char *) &packet, sizeof(pkw_cmd_create_win_t));

    pkw_stat_t status;
    read(sock_fd, (char *) &status, sizeof(pkw_stat_t));

    if (status.status != PKW_STAT_OK) {
        printf("Oh deary me!\n");
        return 1;
    }

    uint16_t window_id = status.header.window_id;

    printf("Created window with id %i\n", (int) window_id);

    pkw_cmd_move_win_t move_win = {
        .header = {
            .command = PKW_CMD_MOVE_WIN,
            .size = sizeof(pkw_cmd_move_win_t),
            .window_id = window_id,
        },
        .x = 50,
        .y = 50,
    };
    write(sock_fd, (char *) &move_win, sizeof(pkw_cmd_move_win_t));
}
