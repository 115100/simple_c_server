#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>

#include "ls.h"
#include "string.h"


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
            // If directory, recurse.
            if (dp->d_type == DT_DIR)
            {
                char newFolder[PATH_MAX];

                if (dir[strlen(dir) - 1] == '/')
                {
                    strcat(newFolder, dir);
                }

                else
                {
                    strcat(newFolder, dir);
                    strcat(newFolder, "/");
                }


                list_files(strcat(newFolder, dp->d_name));
            }

            else
            {
                sprintf(name, "%s/%s", dir, dp->d_name);
                printf("%s\n", name);
            }
        }

    }
}
