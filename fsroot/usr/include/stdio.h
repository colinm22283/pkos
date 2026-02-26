#include <stddef.h>
#include <stdarg.h>

typedef int FILE;

#define SEEK_SET (1)

#define stderr (2)

FILE * fopen(const char * path, const char * options);
int fclose(FILE * stream);

size_t fread(size_t size, size_t n, void * ptr, FILE * stream);
size_t fwrite(size_t size, size_t n, const void * ptr, FILE * stream);
int fseek(FILE * stream, long offset, int whence);
long ftell(FILE * stream);

int setbuf(FILE * stream, char * buf);

int fflush(FILE * stream);
int fprintf(FILE * restrict stream, const char * restrict format, ...);
int vfprintf(FILE * restrict stream, const char * restrict format, va_list ap);

int sprintf(char * restrict s, const char * restrict format, ...);

