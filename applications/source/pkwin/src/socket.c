#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <socket.h>
#include <state.h>
#include <packet.h>

int sock_fd;

__attribute__((noreturn)) void connection_handler(void);

void socket_init(void) {
    printf("Open socket\n");
    sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (sock_fd < 0) {
        printf("Error opening server socket: %s\n", strerrordesc_np(-sock_fd));
        return;
    }

    char addr_buffer[512];
    sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
    strcpy(sockaddr->path, "/tmp/pkw.sock");

    printf("bind()\n");

    int bind_result = bind(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1);
    if (bind_result < 0) {
        printf("Error binding server socket: %s\n", strerrordesc_np(-bind_result));
        return;
    }

    printf("listen()\n");

    int listen_result = listen(sock_fd, 3);
    if (listen_result < 0) {
        printf("Unable to listen on server socket: %s\n", strerrordesc_np(-listen_result));
        return;
    }

    thread(connection_handler);
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

        if (header == NULL) continue;

        acquire(&window_lock);

        switch (header->command) {
            case PKW_CMD_CREATE_WIN: {
                pkw_cmd_create_win_t * cmd = (pkw_cmd_create_win_t *) header;

                /* printf("Create window with name: %s\n", cmd->title); */

                window_count++;
                windows = realloc(windows, window_count * sizeof(window_t *));

                window_t * window = windows[window_count - 1] = window_init(cmd->title, 40, 40, sock_fd, cmd->header.window_id);
            } break;

            case PKW_CMD_MOVE_WIN: {
                pkw_cmd_move_win_t * cmd = (pkw_cmd_move_win_t *) header;

                uint16_t window_id = cmd->header.window_id;

                window_t * window = windows[window_id];

                window->x = cmd->x;
                window->y = cmd->y;
            } break;

            case PKW_CMD_SEND_PIXELS: {
                pkw_cmd_send_pixels_t * cmd = (pkw_cmd_send_pixels_t *) header;

                uint16_t window_id = cmd->header.window_id;

                window_t * window = windows[window_id];

                for (int i = 0; i < cmd->header.size - sizeof(pkw_cmd_header_t); i++) {
                    window->fb[i] = cmd->pixels[i];
                }
            } break;

            case PKW_CMD_DRAW_CHAR: {
                pkw_cmd_draw_char_t * cmd = (pkw_cmd_draw_char_t *) header;

                uint16_t window_id = cmd->header.window_id;

                window_t * window = windows[window_id];

                window_draw_char(window, cmd->c, cmd->x, cmd->y);
            } break;

            case PKW_CMD_RESIZE: {
                pkw_cmd_resize_t * cmd = (pkw_cmd_resize_t *) header;

                uint16_t window_id = cmd->header.window_id;

                window_t * window = windows[window_id];

                window_resize(window, cmd->w, cmd->h);
            } break;
        }

        release(&window_lock);
    }
}

