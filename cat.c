#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "cat.h"
#include "string.h"


int cat(char *file, char **body)
{
    FILE *fp;

    if ((fp = fopen(file, "r")) == NULL)
    {
        fprintf(stderr, "Can't open file %s\n", file);
        return 1;
    }

    int c;
    long int fileLength;

    fseek(fp, 0, SEEK_END);

    fileLength = ftell(fp);

    rewind(fp);

    // Null byte?
    char *newPtr = malloc(sizeof(char) * fileLength + 2);

    *body = newPtr;

    // There's probably a better way to do this
    while ((c = getc(fp)) != EOF)
    {
        *newPtr = (char) c;
        newPtr++;
    }

    // Terminating byte
    *newPtr = '\0';

    fclose(fp);

    // Don't forget to free body
    return 0;
}
