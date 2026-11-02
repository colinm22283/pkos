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

    printf("argc = %i\n", argc);
    printf("argv =\n");
    for (int i = 0; i < argc; i++) {
        printf("  %s\n", argv[i]);
    }

    return 0;
}
