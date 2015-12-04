#ifndef STRING_H
#define STRING_H
#include <stddef.h>

void *memcpy(void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *s);

#endif // STRING_H
