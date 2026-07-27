#include <stdint.h>

#include <unistd.h>

#include <packet.h>

uint16_t current_window_id = 0;

char command_buffer[512];

pkw_cmd_header_t * receive_command(int sock_fd) {
    read(sock_fd, command_buffer, sizeof(pkw_cmd_header_t));

    pkw_cmd_header_t * header = (pkw_cmd_header_t *) command_buffer;

    read(sock_fd, command_buffer + sizeof(pkw_cmd_header_t), header->size - sizeof(pkw_cmd_header_t));

    uint16_t win_id = header->window_id;

    switch (header->command) {
        case PKW_CMD_CREATE_WIN: {
            if (header->size != sizeof(pkw_cmd_create_win_t)) return NULL;

            win_id = current_window_id++;
        } break;

        case PKW_CMD_MOVE_WIN: {
            if (header->size != sizeof(pkw_cmd_move_win_t)) return NULL;
        } break;

        default: {
            send_status(sock_fd, PKW_STAT_INV_CMD, 0);

            return NULL;
        } break;
    }

    send_status(sock_fd, PKW_STAT_OK, win_id);

    return (pkw_cmd_header_t *) command_buffer;
}

void send_status(int sock_fd, uint16_t status, uint16_t window_id) {
    static pkw_stat_t message;

    message.header.command = PKW_STAT;
    message.header.window_id = window_id;
    message.header.size = sizeof(pkw_stat_t);
    message.status = status;

    write(sock_fd, (char *) &message, sizeof(pkw_stat_t));
}
