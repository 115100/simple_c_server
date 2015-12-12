#ifndef STRING_H
#define STRING_H
#include <stddef.h>

void *memcpy(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);
char *strcat(char *s1, const char *s2);
int strcmp(const char *s1, const char *s2);
size_t strlen(const char *s);

#endif // STRING_H
