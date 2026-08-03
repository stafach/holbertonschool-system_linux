#include "hls.h"

/**
* compare - Comparison function for qsort
* @a: first element to compare
* @b: second element to compare
* Return: 0 if all good or 1 if error
*/

int compare(const void *a, const void *b)
{
	/* Compare two strings case-insensitively */
	return (strcasecmp(*(const char **)a, *(const char **)b));
}

/**
* read_names - Read directory entries into a sorted array
* @d: opened directory stream
* @names: pointer to the array of names to fill
* @count: pointer to the count of names
* Return: 0 if all good or 1 if error
*/

int read_names(DIR *d, char ***names, int *count)
{
	/*Create var for read dir*/
	struct dirent *dir;
	char **tmp;

	/* Read directory*/
	while ((dir = readdir(d)) != NULL)
	{
		/* Skip hidden files */
		if (dir->d_name[0] == '.')
			continue;
		/* Allocate memory for the new name */
		tmp = realloc(*names, sizeof(char *) * (*count + 1));
		/* Check for allocation failure */
		if (tmp == NULL)
			return (1);
		/* Update the names pointer */
		*names = tmp;
		/* Duplicate the directory name */
		(*names)[*count] = strdup(dir->d_name);
		/* Check for duplication failure */
		if ((*names)[*count] == NULL)
			return (1);
		/* Increment the count of names */
		(*count)++;
	}
	return (0);
}

/**
* print_names - Print and free the array of names
* @names: array of names to print and free
* @count: number of names in the array
*/

void print_names(char **names, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		if (names[i + 1] != NULL)
			printf("%s  ", names[i]);
		else
			printf("%s", names[i]);
		free(names[i]);
	}
	printf("\n");
	free(names);
}

/**
* main - Entry point
* Return: 0 if all good or 1 if error
*/

int main(void)
{
	/* Create variables for directory and names */
	DIR *d;
	char **names = NULL;
	int count = 0;

	/* Open the current directory */
	d = opendir(".");
	/* Check for errors */
	if (d == NULL)
	{
		perror("opendir");
		return (1);
	}
	/* Read directory and check for errors */
	if (read_names(d, &names, &count) != 0)
	{
		perror("realloc/strdup");
		closedir(d);
		return (1);
	}
	/* Close the directory */
	closedir(d);
	/* Sort the names */
	qsort(names, count, sizeof(char *), compare);
	/* Print the sorted names */
	print_names(names, count);
	return (0);
}
