#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#include <sys/types.h>

typedef struct {
    bool binary;

    int flags;
    fd_t fd;
} FILE;

#define SEEK_SET (1)

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

FILE * fdopen(int fd, const char * options);
FILE * fopen(const char * path, const char * options);
int fclose(FILE * stream);

size_t fread(void * ptr, size_t size, size_t n, FILE * stream);
size_t fwrite(const void * ptr, size_t size, size_t n, FILE * stream);
int fseek(FILE * stream, long offset, int whence);
long ftell(FILE * stream);

int setbuf(FILE * stream, char * buf);

int fflush(FILE * stream);
int fprintf(FILE * restrict stream, const char * restrict format, ...);
int vfprintf(FILE * restrict stream, const char * restrict format, va_list ap);

int sprintf(char * restrict s, const char * restrict format, ...);

void printf(const char * format, ...);
void vprintf(const char * format, va_list args);

