#include <stdint.h>
#include <stdbool.h>

#include <pkos.h>
#include <errno.h>

#include <board.h>

int main(uint64_t argc, const char ** argv) {
    board_init();

    board_draw();

    return 0;
}
