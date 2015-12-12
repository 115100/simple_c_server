#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>

#include "ls.h"
#include "string.h"


int list_files(char *dir, char *search)
{
    char name[PATH_MAX];
    struct dirent *dp;
    DIR *dfd;
    int found = 0;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "Can't open %s\n", dir);
        return -1;
    }

    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
        {
            continue;
        }

        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
        {
            fprintf(stderr, "Can't open %s\n", dir);
        }

        else
        {
            // If directory, recurse; do not compare for search
            if (dp->d_type == DT_DIR)
            {
                char newFolder[PATH_MAX];

                if (dir[strlen(dir) - 1] == '/')
                {
                    strcat(newFolder, dir);
                }

                else
                {
                    sprintf(newFolder, "%s/", dir);
                }

                found = list_files(strcat(newFolder, dp->d_name), search);
            }

            else
            {
                strcat(name, dp->d_name);

                if (strcmp(name, search) == 0)
                {
                    found = 1;
                }
            }
        }

        if (found)
        {
            break;
        }

    }

    closedir(dfd);
    return found;
}
