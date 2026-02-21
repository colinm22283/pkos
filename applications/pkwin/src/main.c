#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#include <main.h>

#include <display.h>
#include <packet.h>

volatile bool lock;

__NORETURN void display_thread(void);

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
    lock = false;

    print("Start display thread\n");
    // thread(display_thread);

    print("Open socket\n");
    fd_t sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (sock_fd < 0) {
        print("Error opening server socket\n");
        cleanup_all();
    }

    char addr_buffer[512];
    sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
    strcpy(sockaddr->path, "/tmp/pkw.sock");

    print("bind()\n");

    error_number_t bind_result = bind(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1);
    if (bind_result < 0) {
        print("Error binding server socket\n");
        cleanup_all();
    }

    print("listen()\n");

    error_number_t listen_result = listen(sock_fd, 3);
    if (listen_result < 0) {
        print("Unable to listen on server socket\n");
        cleanup_all();
    }

    print("Starting accept loop\n");

    while (true) {
        print("wait\n");

        fd_t new_sock = accept(sock_fd);

        print("Socket accepted\n");

        while (true) {
            print("wait\n");

            pkw_cmd_header_t * header = receive_command(new_sock);

            print("Got message\n");

            while (lock) { }
            lock = true;

            print("READING\n");

            switch (header->command) {
                case PKW_CMD_CREATE_WIN: {
                    print("Create window\n");

                    pkw_cmd_create_win_t * cmd = (pkw_cmd_create_win_t *) header;

                    windows_add(cmd->title);
                } break;
            }

            lock = false;

            for (size_t i = 0; i < 1000000; i++) asm volatile("nop");
        }
    }
}

__NORETURN void display_thread(void) {
    display_t display;
    display_init(&display, "/dev/vga", 320, 200);

    display_draw(&display);

    while (true) {
        while (lock) { }
        lock = true;

        display_draw(&display);

        windows_draw(&display);

        lock = false;

        for (size_t i = 0; i < 1000000; i++) asm volatile("nop");
    }
}

void cleanup_all(void) {
    exit(0);
}
