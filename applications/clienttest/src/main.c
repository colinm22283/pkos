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

    print("CLIENT: socket()\n");
    fd_t client_fd = socket(SOCKET_UNIX, SOCKET_STREAM, 0);
    if (client_fd < 0) {
        print("CLIENT: Error opening socket\n");
        return 1;
    }

    error_number_t connect_result;
    do {
        print("CLIENT: connect()\n");
        connect_result = connect(client_fd, (const sockaddr_t *) socket_address, strlen(socket_address->path) + 1);

        if (connect_result != ERROR_OK) print("CLIENT: connect failed\n");

        for (uint64_t i = 0; i < 10000000; i++) asm volatile ("nop");
    }
    while (connect_result != ERROR_OK);

    uint32_t num = 0;

    while (true) {
        write(client_fd, (char *) &num, sizeof(uint32_t));

        read(client_fd, (char *) &num, sizeof(uint32_t));

        print("CLIENT: num = ");
        print_hex(num);
        print("\n");

        for (uint64_t i = 0; i < 10000000; i++) asm volatile ("nop");
    }

    return 0;
}
