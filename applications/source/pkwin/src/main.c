#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include <packet.h>
#include <render.h>
#include <state.h>
#include <window.h>
#include <mouse.h>
#include <cursor.h>
#include <socket.h>
#include <font.h>

#include <sys/file.h>

int main(int argc, const char ** argv) {
    cursor_init();
    font_init();

    state_init();

    socket_init();

    mouse_init();

    render_loop();
}

