#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#include <fcntl.h>
#include <unistd.h>

#include <mouse.h>
#include <state.h>
#include <render.h>

mouse_coord_t mouse_coord = { 0, 0 };

typedef struct __attribute__((packed)) {
    uint32_t type;
    uint8_t  size;

    union {
        struct __attribute__((packed)) {
            uint8_t  action;
            uint16_t code;
        } key;

        struct __attribute__((packed)) {
            uint8_t axis;
            int32_t value;
        } rel;
    };
} input_packet_t;

__attribute__((noreturn)) void mouse_thread(void) {
    int mouse_fd = open("/dev/input0", O_RDONLY);

    while (true) {
        input_packet_t packet;

        if (read(mouse_fd, (char *) &packet, sizeof(input_packet_t))) {
            switch (packet.type) {
                case 1 << 0: {
                    if (packet.key.code == 272) {
                        acquire(&window_lock);

                        if (held_window != NULL && packet.key.action == 1) {
                            held_window = NULL;
                        }
                        else if (packet.key.action == 0) {
                            for (int i = 0; i < window_count; i++) {
                                window_t * window = windows[i];

                                window_click(window, mouse_coord.x, mouse_coord.y);
                            }
                        }

                        release(&window_lock);
                    }
                    else {
                        acquire(&window_lock);

                        if (focus_window != NULL) {
                            if (packet.key.action == 0) {
                                window_press(focus_window, packet.key.code);
                            }
                        }

                        release(&window_lock);
                    }
                } break;

                case 1 << 1: {
                    switch (packet.rel.axis) {
                        case 0: mouse_coord.x += packet.rel.value; break;
                        case 1: mouse_coord.y -= packet.rel.value; break;
                    }

                    if (mouse_coord.x < 0) mouse_coord.x = 0;
                    if (mouse_coord.y < 0) mouse_coord.y = 0;
                    if (mouse_coord.x >= WIDTH) mouse_coord.x = WIDTH - 1;
                    if (mouse_coord.y >= HEIGHT) mouse_coord.y = HEIGHT - 1;
                } break;
            }
        }
    }
}

void mouse_init(void) {
    thread(mouse_thread);
}

mouse_coord_t get_mouse_pos(void) {
    return mouse_coord;
}

