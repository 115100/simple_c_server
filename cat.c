#include <stdio.h>

#include "cat.h"


int cat(char *file)
{
    FILE *fp;

    if ((fp = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", file);
        return 1;
    }

    else
    {
        int c;
        
        while ((c = getc(fp)) != EOF)
        {
            putc(c, stdout); // TODO: Write to response.body
        }
    }

    return 0;
}
