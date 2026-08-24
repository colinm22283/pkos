#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include <dirent.h>

int open_dir(const char * path, int indent) {
    DIR * dir = opendir(path);

    while (true) {
        struct dirent * dirent = readdir(dir);

        if (dirent == NULL) break;

        for (int i = 0; i < indent; i++) {
            printf("| ");
        }
        printf("%s\n", dirent->d_name);

        if (dirent->d_type == FS_DIRECTORY) {
            size_t path_len = strlen(path);
            size_t dir_len  = strlen(dirent->d_name);

            char * new_path = malloc(path_len + dir_len + 2);

            strcpy(new_path + 0, path);
            new_path[path_len] = '/';
            strcpy(new_path + path_len + 1, dirent->d_name);

            open_dir(new_path, indent + 1);

            free(new_path);
        }
    }
}

int main(int argc, const char ** argv) {
    const char * path;

    if (argc == 1) path = ".";
    else if (argc == 2) path = argv[1];
    else {
        printf("Expecting either 0 or 1 arguments\n");
        return 1;
    }

    return open_dir(path, 1);
}
