#include <stdlib.h>
#include <stdbool.h>

#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

DIR * opendir(const char * path) {
    int dir_fd = open(path, O_RDONLY);

    if (dir_fd < 0) return NULL;

    DIR * dir = malloc(sizeof(DIR));
    
    dir->fd = dir_fd;
    dir->size = 64;
    dir->buffer = malloc(dir->size);

    return dir;
}

struct dirent * readdir(DIR * dir) {
    while (true) {
        int readdir_result = sys_readdir(dir->fd, (struct dirent *) dir->buffer, dir->size);

        if (readdir_result == 0) return NULL;
        else if (readdir_result == -ERANGE) {
            dir->size *= 2;
            dir->buffer = realloc(dir->buffer, dir->size);
        }
        else if (readdir_result == 1) {
            return (struct dirent *) dir->buffer;
        }
        else {
            return NULL;
        }
    }
}

int closedir(DIR * dir) {
    close(dir->fd);

    free(dir->buffer);
    free(dir);
}

