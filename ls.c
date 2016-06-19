#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>

#include "ls.h"
#include "string.h"


int find_resource(const char *dir, char *search)
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
			continue;

		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "Can't open %s\n; path too long", dir);

		else
		{
			// If directory, recurse; do not compare for search
			if (dp->d_type == DT_DIR)
			{
				char newFolder[PATH_MAX];
				memset(newFolder, 0, PATH_MAX);

				if (dir[strlen(dir) - 1] == '/')
					strcat(newFolder, dir);

				else
					sprintf(newFolder, "%s/", dir);

				strcat(newFolder, dp->d_name);
				found = find_resource(newFolder, search);
			}

			else
			{
				sprintf(name, "%s/%s", dir, dp->d_name);

				if (strcmp(name, search) == 0)
					found = 1;
			}
		}

		if (found)
			break;

	}

	closedir(dfd);
	return found;
}
