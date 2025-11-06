#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

static inline void print_hex(uint64_t num) {
    char data[17];

    for (int i = 15; i >= 0; i--) {
        uint64_t val = num % 16;

        char c;
        if (val < 10) c = (char) ('0' + val);
        else c = (char) ('A' + val - 10);

        data[i] = c;
        num /= 16;
    }

    data[16] = '\0';

    print(data);
}

static inline bool streq(const char * a, const char * b) {
    while (true) {
        if (*a != *b) {
            return false;
        }
        else {
            if (*a == '\0') return true;
        }

        a++;
        b++;
    }
}

uint64_t strlen(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;
    return str_size;
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

uint64_t strcmp(const char * a, const char * b) {
    uint64_t i;

    for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }

    return a[i] - b[i];
}

int main(uint64_t argc, const char ** argv) {
    char socket_buffer[512];

    sockaddr_unix_t * socket_address = (sockaddr_unix_t *) &socket_buffer;
    strcpy(socket_address->path, "/tmp/yep");

    print("socket()\n");
    fd_t server_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (server_fd < 0) {
        print("Error openning socket\n");
        return 1;
    }

    print("bind()\n");
    error_number_t bind_result = bind(server_fd, (const sockaddr_t *) socket_address, strlen(socket_address->path) + 1);
    if (bind_result != ERROR_OK) {
        print("Error while binding server socket\n");
        return 1;
    }

    print("listen()\n");
    error_number_t listen_result = listen(server_fd, 3);
    if (listen_result != ERROR_OK) {
        print("Error while starting socket listen\n");
        return 1;
    }

    print("fork()\n");
    pid_t fork_result = fork();

    if (fork_result == 0) {
        print("Child\n");

        print("accept()\n");
        fd_t client_fd = accept(server_fd);

        if (client_fd < 0) {
            print("SERVER: Unable to accept connection\n");
            return 1;
        }

        print("Server read\n");
        char buffer[256];
        read(client_fd, buffer, 6);
        write(stdout, buffer, 6);
    }
    else {
        print("Parent\n");

        print("socket()\n");
        fd_t sock_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
        if (sock_fd < 0) {
            print("Error openning socket\n");
            exit(1);
        }

        print("connect()\n");
        error_number_t connect_result = connect(sock_fd, (const sockaddr_t *) socket_address, strlen(socket_address->path) + 1);
        if (connect_result != ERROR_OK) {
            print("Unable to connect socket\n");
            exit(1);
        }

        print("Client write\n");
        write(sock_fd, "hello\n", 6);
    }

    return 0;
}
