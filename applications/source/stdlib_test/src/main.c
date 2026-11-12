#include <stdbool.h>
#include <stdio.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, const char ** argv) {
    /* int mouse_fd = open("/dev/mouse0", O_RDONLY); */

    /* char packet[3]; */

    /* while (true) { */
        /* if (read(mouse_fd, packet, 3)) { */
            /* printf("(%i, %i)\n", packet[1], packet[2]); */
        /* } */
    /* } */

    int fd = open("/dev/vga", O_RDWR);

    char * fb = map(fd, NULL, 320 * 200, 0, MAP_WRITE);

    printf("Got %i as fb vaddr\n", (int) fb);

    for (int i = 0; i < 320 * 200; i++) {
        fb[i] = 2;
    }

    return 0;
}
