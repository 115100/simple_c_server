#include <dirent.h>
#include <limits.h>
#include <stdio.h>

#include "include/ls.h"
#include "include/string.h"

void list_files(char *dir)
{
    char name[PATH_MAX];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", dir);
        return;
    }

    while ((dp = readdir(dfd)) != NULL)
    {
        if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
        {
            continue;
        }

        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
        {
            fprintf(stderr, "Can't open %s\n", dir);
        }

        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            printf("%s\n", name);
        }
    }
}
