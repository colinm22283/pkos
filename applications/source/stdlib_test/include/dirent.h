#pragma once

#include <stdint.h>
#include <stddef.h>

#include <sys/types.h>

#include <pkos/syscalls.h>

struct dirent {
    fs_file_type_t d_type;
    uint64_t d_size;

    ino_t d_ino;
    char d_name[];
};

typedef struct {
    int fd;

    size_t size;
    char * buffer;
} DIR;

DEFINE_SYSCALL3(SYSCALL_READDIR, int, sys_readdir, int, fd, struct dirent *, dirents, size_t, size);

DIR * opendir(const char * path);
struct dirent * readdir(DIR * dir);
int closedir(DIR * dir);


