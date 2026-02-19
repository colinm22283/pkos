#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

#define BUFFER_SIZE (1024)

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);

    exit(1);
}

void alarm_handler(signal_number_t sig) {
    print("ALARM RECIEVED\n");
}

int main(uint64_t argc, const char ** argv) {
    signal(SIG_ALARM, alarm_handler);

    alarm(1);

    char c;
    read(stdin, &c, 1);
    read(stdin, &c, 1);
    read(stdin, &c, 1);
    read(stdin, &c, 1);
    read(stdin, &c, 1);

    return 0;
}
