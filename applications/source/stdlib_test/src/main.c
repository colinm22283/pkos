#include <stdbool.h>
#include <stdio.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, const char ** argv) {
    int mouse_fd = open("/dev/mouse0", O_RDONLY);

    char packet[3];

    while (true) {
        if (read(mouse_fd, packet, 3)) {
            printf("(%i, %i)\n", packet[1], packet[2]);
        }
    }

    return 0;
}
