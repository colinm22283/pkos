#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#define BUFFER_SIZE (10)

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

void run_line(char * line);

int main(uint64_t argc, const char ** argv) {
    int64_t line_size = 0;
    static char line_buf[512];

    if (argc == 1) {
        while (true) {
            print("> ");

            while (true) {
                char c;
                read(stdin, &c, 1);

                if (c == '\n') {
                    line_buf[line_size] = '\0';
                    break;
                }
                else {
                    line_buf[line_size] = c;

                    line_size++;
                }
            }

            run_line(line_buf);

            line_size = 0;
        }
    }
    else if (argc == 2) {
        fd_t in_fd = open(argv[1], OPEN_READ);

        while (true) {
            while (true) {
                int64_t amount_read = read(in_fd, line_buf + line_size, 1);

                if (amount_read == 0 || line_buf[line_size] == '\n') {
                    line_buf[line_size] = '\0';
                    break;
                }
                else line_size++;
            }

            if (line_size == 0) break;
            run_line(line_buf);
            line_size = 0;
        }

        close(in_fd);
    }
    else {
        print("Invalid arguments\n");
    }

    return 0;
}

void run(char ** argv, uint64_t argc, fd_t in, fd_t out, bool background) {
    uint64_t pipe_pos = 0;
    for (uint64_t i = 0; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_pos = i;

            fd_t pipe_fds[2];
            pipe(pipe_fds, 0);

            run(argv, pipe_pos, in, pipe_fds[0], false);
            run(argv + pipe_pos + 1, argc - pipe_pos - 1, pipe_fds[1], out, false);

            return;
        }
        else if (strcmp(argv[i], ">") == 0) {
            pipe_pos = i;

            fd_t out_file = open(argv[pipe_pos + 1], OPEN_WRITE | OPEN_CREATE);

            run(argv, pipe_pos, in, out_file, false);

            return;
        }
        else if (strcmp(argv[i], "&") == 0) {
            pipe_pos = i;

            run(argv, pipe_pos, in, out, true);

            return;
        }
    }

    if (streq(argv[0], "cd")) {
        if (chdir(argv[1]) != ERROR_OK) {
            print("cd: Unable to change directory\n");
        }
    }
    else if (streq(argv[0], "exit")) {
        exit(0);
    }
    else {
        pid_t fork_result = fork();

        if (fork_result == 0) { // child
            char path[5 + strlen(argv[0]) + 1];
            strcpy(path, "/bin/");
            strcpy(path + 5, argv[0]);

            dup(stdout, out);
            dup(stdin, in);

            error_number_t exec_result = exec(path, (const char **) argv, argc);

            if (exec_result != ERROR_OK) {
                print("Unable to execute \"");
                print(argv[0]);
                print("\"\n");

                exit(1);
            }
            else exit(0);
        }
        else { // parent
            if (!background) wait();
        }
    }
}

void run_line(char * line) {
    if (line[0] == '\0') return;

    int argc = 1;
    char * argv[100] = { line };

    for (uint64_t i = 0; line[i] != '\0'; i++) {
        if (line[i] == ' ') {
            line[i] = '\0';

            argv[argc++] = &line[i + 1];
        }
    }

    run(argv, argc, stdin, stdout, false);
}
