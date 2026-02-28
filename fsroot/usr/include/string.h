#include <stddef.h>

void * memcpy(void * dst, void * src, size_t size);
void * memset(void * dst, int val, size_t size);
size_t strlen(const char * str);

char * strcpy(char * restrict dst, const char * restrict src);
char * strcat(char * restrict dst, const char * restrict src);
char * strchr(const char * s, int c);
int strcmp(const char * dst, const char * src);

