#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

volatile bool gaming = false;

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

void alarm_handler(signal_number_t sig) {
    print("ALARM RECIEVED\n");

    gaming = true;
}

int main(uint64_t argc, const char ** argv) {
    signal(SIG_ALARM, alarm_handler);

    alarm(1);

    while (true) {
        print("yep\n");

        if (gaming) break;
    }

    print("bye\n");

    return 0;
}
