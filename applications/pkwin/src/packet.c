#include <pkos.h>

#include <packet.h>
#include <window.h>

pkw_cmd_header_t * receive_command(fd_t sock_fd) {
    static char command_buffer[512];

    read(sock_fd, command_buffer, sizeof(pkw_cmd_header_t));

    pkw_cmd_header_t * header = (pkw_cmd_header_t *) command_buffer;

    read(sock_fd, command_buffer + sizeof(pkw_cmd_header_t), header->size - sizeof(pkw_cmd_header_t));

    switch (header->command) {
        case PKW_CMD_CREATE_WIN: {
            if (header->size != sizeof(pkw_cmd_create_win_t)) return NULL;
        } break;

        case PKW_CMD_MOVE_WIN: {
            if (header->size != sizeof(pkw_cmd_move_win_t)) return NULL;
        } break;

        default: {
            send_status(sock_fd, PKW_STAT_INV_CMD);

            return NULL;
        } break;
    }

    send_status(sock_fd, PKW_STAT_OK);

    return (pkw_cmd_header_t *) &command_buffer;
}

void send_status(fd_t sock_fd, uint16_t status) {
    static pkw_stat_t message;

    message.header.command = PKW_STAT;
    message.header.window_id = 0;
    message.header.size = sizeof(pkw_stat_t);
    message.status = status;

    write(sock_fd, (char *) &message, sizeof(pkw_stat_t));
}
