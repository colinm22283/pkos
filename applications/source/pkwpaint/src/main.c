#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <packet.h>
#include <image.h>
#include <bmp.h>

image_t im;

int main(int argc, const char ** argv) {
    if (argc != 2) {
        printf("Usage: %s <bmp path>\n", argv[0]);
        return 1;
    }

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

    strcpy(packet.title, "pkwview");

    write(sock_fd, (char *) &packet, sizeof(pkw_cmd_create_win_t));

    pkw_stat_t status;
    read(sock_fd, (char *) &status, sizeof(pkw_stat_t));

    if (status.status != PKW_STAT_OK) {
        printf("Oh deary me!\n");
        return 1;
    }

    uint16_t window_id = status.header.window_id;

    bmp_load(&im, argv[1]);

    pkw_cmd_resize_t resize = {
        .header = {
            .command = PKW_CMD_RESIZE,
            .size = sizeof(pkw_cmd_resize_t),
            .window_id = window_id,
        },
        .w = im.w,
        .h = im.h,
    };

    write(sock_fd, (char *) &resize, sizeof(pkw_cmd_resize_t));

    read(sock_fd, (char *) &status, sizeof(pkw_stat_t));

    if (status.status != PKW_STAT_OK) {
        printf("Oh deary me!\n");
        return 1;
    }

    char * _send_pixels = malloc(sizeof(pkw_cmd_header_t) + im.w * im.h);
    pkw_cmd_send_pixels_t * send_pixels = _send_pixels;

    send_pixels->header.command   = PKW_CMD_SEND_PIXELS;
    send_pixels->header.size      = sizeof(pkw_cmd_header_t) + im.w * im.h;
    send_pixels->header.window_id = window_id;

    for (int i = 0; i < im.w * im.h; i++) send_pixels->pixels[i] = im.pixels[i];

    write(sock_fd, (char *) _send_pixels, sizeof(pkw_cmd_header_t) + im.w * im.h);

    read(sock_fd, (char *) &status, sizeof(pkw_stat_t));

    if (status.status != PKW_STAT_OK) {
        printf("Oh deary me!\n");
        return 1;
    }

    free(_send_pixels);
}

