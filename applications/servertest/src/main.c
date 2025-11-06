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
    strcpy(socket_address->path, "/tmp/test.sock");

    print("SERVER: socket()\n");
    fd_t server_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (server_fd < 0) {
        print("SERVER: Error openning socket\n");
        return 1;
    }

    print("SERVER: bind()\n");
    error_number_t bind_result = bind(server_fd, (const sockaddr_t *) socket_address, strlen(socket_address->path) + 1);
    if (bind_result != ERROR_OK) {
        print("SERVER: Error while binding server socket\n");
        return 1;
    }

    print("SERVER: listen()\n");
    error_number_t listen_result = listen(server_fd, 3);
    if (listen_result != ERROR_OK) {
        print("SERVER: Error while starting socket listen\n");
        return 1;
    }

    print("SERVER: accept()\n");
    fd_t conn_fd = accept(server_fd);
    if (conn_fd < 0) {
        print("SERVER: Failed to accept client\n");
        return 1;
    }

    while (true) {
        uint32_t num;

        read(conn_fd, (char *) &num, sizeof(uint32_t));

        num++;

        write(conn_fd, (char *) &num, sizeof(uint32_t));
    }

    return 0;
}
