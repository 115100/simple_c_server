#include <stddef.h>
#include <string.h>

void *memcpy(void *s1, const void *s2, size_t n)
{
    char *dest = s1;
    const char *source = s2;

    for (int i=0; i<n; i++)
    {
        dest[i] = source[i];
    }
} 
