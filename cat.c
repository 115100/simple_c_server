#include <stdio.h>
#include <stdlib.h>

#include "cat.h"
#include "string.h"


int cat(char *file, char *body)
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

    fseek(fp, 0, SEEK_SET);

    char *originalPointer = body;

    // Null byte?
    body = malloc(fileLength + 2);

    // There's probably a better way to do this
    while ((c = getc(fp)) != EOF)
    {
        *originalPointer = (char) c;
        originalPointer++;
    }

    // Terminating byte
    *originalPointer = '\0';

    close(fp);

    // Don't forget to free *body
    return 0;
}
