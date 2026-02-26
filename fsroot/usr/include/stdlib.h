#include <stddef.h>

void abort(void);

void * malloc(size_t size);
void free(void * alloc);
void * calloc(size_t num, size_t size);

int atexit(void (*function)(void));

int atoi(const char * nptr);

char * getenv(const char * name);

int abs(int j);

