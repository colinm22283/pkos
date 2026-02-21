#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <error_number.h>

static inline void print(const char * str) {
    uint64_t str_size = 0;
    while (str[str_size] != '\0') str_size++;

    write(stdout, str, str_size);
}

__NORETURN void thread_start(void) {
    print("TEST\n");

    while (true) { }
}

int main(uint64_t argc, const char ** argv) {
    thread(thread_start);

    print("aaa\n");

    return 0;
}
