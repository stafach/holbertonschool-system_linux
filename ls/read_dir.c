#include "hls.h"

/**
* count_entries - Count non-hidden entries in a directory
* @d: opened directory stream
* Return: number of entries found
*/

int count_entries(DIR *d)
{
	struct dirent *dir;
	int count = 0;

	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
			count++;
	}
	return (count);
}

/**
* fill_names - Read directory entries into a names array
* @d: opened directory stream
* @names: pre-allocated array to fill
* Return: 0 if all good or 1 if error
*/

int fill_names(DIR *d, char **names)
{
	struct dirent *dir;
	int i = 0;

	while ((dir = readdir(d)) != NULL)
	{
		if (dir->d_name[0] != '.')
		{
			names[i] = my_strdup(dir->d_name);
			if (names[i] == NULL)
				return (1);
			i++;
		}
	}
	return (0);
}
