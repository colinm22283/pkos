#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#include <main.h>

#include <display.h>
#include <packet.h>

volatile bool lock;

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

    // fd_t bind_fd = open("/sys/vgatty/bind", OPEN_WRITE);
    // write(bind_fd, "0", 1);
    // close(bind_fd);

    print("Fork init window\n");
    {
        pid_t temp = fork();
        if (temp == 0) {
            const char * args[] = { "/bin/pkwball" };
            exec("/bin/pkwball", args, 1);
        }
    }

    print("Init main display\n");
    display_t main_display;
    display_init(&main_display, "/dev/vga", 320, 200);

    print("Starting main loop\n");
    pid_t fork_result = fork();

    if (fork_result == 0) {
        accept_loop();
    }
    else {
        while (true) {
            while (lock) { }
            lock = true;

            // display_draw(&main_display);

            lock = false;

            for (uint64_t i = 0; i < 10000; i++) asm volatile ("nop");
        }
    }
}

void cleanup_all(void) {
    fd_t bind_fd = open("/sys/vgatty/bind", OPEN_WRITE);
    write(bind_fd, "1", 1);
    close(bind_fd);

    exit(0);
}

__NORETURN void accept_loop(void) {
    print("Open socket\n");
    fd_t sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (sock_fd < 0) {
        print("Error opening server socket\n");
        cleanup_all();
    }

    char addr_buffer[512];
    sockaddr_unix_t * sockaddr = (sockaddr_unix_t *) addr_buffer;
    strcpy(sockaddr->path, "/tmp/pkw.sock");

    error_number_t bind_result = bind(sock_fd, (const sockaddr_t *) sockaddr, strlen(sockaddr->path) + 1);
    if (bind_result < 0) {
        print("Error binding server socket\n");
        cleanup_all();
    }

    error_number_t listen_result = listen(sock_fd, 3);
    if (listen_result < 0) {
        print("Unable to listen on server socket\n");
        cleanup_all();
    }

    print("Starting accept loop\n");

    while (true) {
        fd_t new_sock = accept(sock_fd);

        print("Socket accepted\n");

        pid_t fork_result = fork();

        if (fork_result == 0) {
            listen_loop(new_sock);
        }
    }
}

void listen_loop(fd_t sock_fd) {
    while (true) {
        pkw_cmd_header_t * header = receive_command(sock_fd);

        print("Got message\n");

        while (!lock) { }
        lock = true;

        switch (header->command) {
            case PKW_CMD_CREATE_WIN: {
                pkw_cmd_create_win_t * cmd = (pkw_cmd_create_win_t *) header;

                windows_add(cmd->title);
            } break;
        }

        lock = false;
    }
}
