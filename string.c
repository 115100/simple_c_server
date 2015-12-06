#include "string.h"

void *memcpy(void *s1, const void *s2, size_t n)
{
    char *dest = s1;
    const char *source = s2;

    for (int i=0; i<n; i++)
    {
        dest[i] = source[i];
    }

    return s1;
} 

void *memset(void *s, int c, size_t n)
{
    char *dest = s;
    const char copyChar = (char) c;

    for (int i=0; i<n; i++)
    {
        dest[i] = copyChar;
    }

    return s;
}


int strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            break;
        }

        i++;
    }

    return s1[i] - s2[i];
}

size_t strlen(const char *s)
{
   const char *c;

   for (c = s; *c; ++c)
       ;

   return (c - s);
}
