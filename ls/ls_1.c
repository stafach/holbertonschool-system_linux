#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/**
* compare - Comparison function for qsort
* @a: first element to compare
* @b: second element to compare
* Return: 0 if all good or 1 if error
*/

int compare(const void *a, const void *b)
{
	/* Compare the two strings, ignoring case */
	return (strcasecmp(*(const char **)a, *(const char **)b));
}


/**
* main - Entry point
* Return: 0 if all good or 1 if error
*/

int main(void)
{
	/* Create var for directory */
	DIR *d;

	/* Open the current directory */
	d = opendir(".");
	/* Check if the directory was opened successfully */
	if (d == NULL)
	{
		perror("opendir");
		return (1);
	}

	/* Create variables needed */
	struct dirent *dir;
	char **names = NULL;
	int count = 0;

	/* Read the directory */
	while ((dir = readdir(d)) != NULL)
	{
		/* Skip hidden files */
		if (dir->d_name[0] == '.')
			continue;

		/* Alloc the memory for each names */
		names = realloc(names, sizeof(char *) * (count + 1));
		/* Check if realloc was successful */
		if (names == NULL)
		{
			perror("realloc");
			closedir(d);
			return (1);
		}
		/* Duplicate the directory name */
		names[count] = strdup(dir->d_name);
		/* Check if strdup was successful */
		if (names[count] == NULL)
		{
			perror("strdup");
			closedir(d);
			return (1);
		}
		/* Increment the count of names */
		count++;
	}
	/* Close the directory */
	closedir(d);
	/* Sort the names in alphabetical order */
	qsort(names, count, sizeof(char *), compare);
	/* Print the sorted names */
	for (int i = 0; i < count; i++)
	{
		printf("%s ", names[i]);
		free(names[i]);
	}
	free(names);
	return (0);
}
