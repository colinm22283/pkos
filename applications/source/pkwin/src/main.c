#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <packet.h>

#include <sys/file.h>

#define WIDTH (320)
#define HEIGHT (200)
uint8_t * fb;

typedef struct {
    int x, y, w, h;
} window_t;

size_t window_count;
window_t * windows;

int sock_fd;

bool connection_gained = false;
__attribute__((noreturn)) void connection_handler(void);
void render(void);

int main(int argc, const char ** argv) {
    int fb_fd = open("/dev/vga", O_RDWR);
    fb = map(fb_fd, NULL, WIDTH * HEIGHT, 0, MAP_WRITE);

    window_count = 0;
    windows = malloc(1);

    printf("Open socket\n");
    sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (sock_fd < 0) {
        printf("Error opening server socket: %s\n", strerrordesc_np(-sock_fd));
        return 1;
    }

    char addr_buffer[512];
    sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
    strcpy(sockaddr->path, "/tmp/pkw.sock");

    printf("bind()\n");

    int bind_result = bind(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1);
    if (bind_result < 0) {
        printf("Error binding server socket: %s\n", strerrordesc_np(-bind_result));
        return 1;
    }

    printf("listen()\n");

    int listen_result = listen(sock_fd, 3);
    if (listen_result < 0) {
        printf("Unable to listen on server socket: %s\n", strerrordesc_np(-listen_result));
        return 1;
    }

    render();

    connection_handler();
}

__attribute__((noreturn)) void connection_handler(void) {
    int new_sock = accept(sock_fd);

    if (new_sock < 0) {
        printf("Accept returned error: %s\n", strerrordesc_np(-new_sock));
        connection_handler();
    }

    printf("Got new connection!\n");

    thread(connection_handler);

    while (1) {
        pkw_cmd_header_t * header = receive_command(new_sock);

        switch (header->command) {
            case PKW_CMD_CREATE_WIN: {
                pkw_cmd_create_win_t * cmd = (pkw_cmd_create_win_t *) header;

                // printf("Create window with name: %s\n", cmd->title);

                window_count++;
                windows = realloc(windows, window_count * sizeof(window_t));

                window_t * window = &windows[window_count - 1];

                window->x = 10;
                window->y = 10;
                window->w = 40;
                window->h = 40;
            } break;

            case PKW_CMD_MOVE_WIN: {
                pkw_cmd_move_win_t * cmd = (pkw_cmd_move_win_t *) header;

                uint16_t window_id = cmd->header.window_id;

                window_t * window = &windows[window_id];

                window->x = cmd->x;
                window->y = cmd->y;
            } break;
        }

        render();
    }
}

void render(void) {
    for (size_t x = 0; x < WIDTH; x++) {
        for (size_t y = 0; y < HEIGHT; y++) {
            fb[y * WIDTH + x] = 2;
        }
    }

    for (size_t i = 0; i < window_count; i++) {
        window_t * window = &windows[i];

        for (size_t x = window->x; x < window->x + window->w; x++) {
            for (size_t y = window->y; y < window->y + window->h; y++) {
                fb[y * WIDTH + x] = 3;
            }
        }
    }
}
