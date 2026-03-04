#pragma once

typedef struct _FILE_s {
    bool binary;

    int flags;
    fd_t fd;
} FILE;
