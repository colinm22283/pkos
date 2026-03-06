#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <errno.h>

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
    print("fork()\n");
    pid_t fork_result = fork();

    if (fork_result == 0) {
        const char * args[1] = { "/bin/clienttest" };
        exec(args[0], args, 1);
    }
    else {
        fork_result = fork();

        if (fork_result == 0) {
            const char * args[1] = { "/bin/servertest" };
            exec(args[0], args, 1);
        }
    }

    return 0;
}
