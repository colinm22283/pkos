#include <stdbool.h>

#include <fcntl.h>
#include <unistd.h>

#include <mouse.h>
#include <state.h>

bool prev_bl = false;
mouse_coord_t mouse_coord = { 0, 0 };

__attribute__((noreturn)) void mouse_thread(void) {
    int mouse_fd = open("/dev/mouse0", O_RDONLY);

    char packet[3];

    while (true) {
        if (read(mouse_fd, packet, 3)) {
            mouse_coord.x += packet[1];
            mouse_coord.y += -packet[2];

            if (mouse_coord.x < 0) mouse_coord.x = 0;
            if (mouse_coord.y < 0) mouse_coord.y = 0;
            if (mouse_coord.x >= 640) mouse_coord.x = 639;
            if (mouse_coord.y >= 480) mouse_coord.y = 479;

            bool new_bl = !!(packet[0] & 1);

            if (new_bl && !prev_bl) {
                acquire(&window_lock);

                if (held_window != NULL) {
                    held_window = NULL;
                }
                else {
                    for (int i = 0; i < window_count; i++) {
                        window_t * window = windows[i];

                        window_click(window, mouse_coord.x, mouse_coord.y);
                    }
                }

                release(&window_lock);
            }

            prev_bl = new_bl;
        }
    }
}

void mouse_init(void) {
    thread(mouse_thread);
}

mouse_coord_t get_mouse_pos(void) {
    return mouse_coord;
}

