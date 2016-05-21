#include <stddef.h>

#include "string.h"


void *memcpy(void *s1, const void *s2, size_t n)
{
	char *dest = s1;
	const char *source = s2;

	for (size_t i=0; i<n; i++)
	{
		dest[i] = source[i];
	}

	return s1;
} 


void *memset(void *s, int c, size_t n)
{
	char *dest = s;
	const char copyChar = (char) c;

	for (size_t i=0; i<n; i++)
	{
		dest[i] = copyChar;
	}

	return s;
}


char *strcat(char *s1, const char *s2)
{
	while (*s1)
	{
		s1++;
	}

	while (*s1++ = *s2++);

	return s1;
}


int strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			break;
		}

		s1++;
		s2++;
	}

	return *s1 - *s2;
}
