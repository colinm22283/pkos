#include <stdbool.h>
#include <stdio.h>

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, const char ** argv) {
    DIR * dir = opendir(".");

    while (true) {
        struct dirent * dirent = readdir(dir);

        if (dirent == NULL) break;
        
        printf("%s\n", dirent->d_name);
    }

    closedir(dir);

    return 0;
}
