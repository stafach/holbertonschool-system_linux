#include "hls.h"

/**
* main - Entry point
* Return: 0 on success, 1 or 2 on error
*/

int main(void)
{
	DIR *d;
	char **names;
	int count;

	d = opendir(".");
	if (d == NULL)
	{
		perror("ls: cannot open directory '.'");
		return (2);
	}
	count = count_entries(d); /* Count entries */
	closedir(d); /* Close directory for reload readdir */

	names = malloc(sizeof(char *) * count); /* Allocate memory each entry*/
	if (names == NULL)
	{
		fprintf(stderr, "ls: memory allocation failed\n");
		return (1);
	}
	d = opendir("."); /* Reopen directory from the beginning */
	if (d == NULL)
	{
		perror("ls: cannot open directory '.'");
		free(names);
		return (2);
	}
	if (fill_names(d, names) != 0) /* Check if fill_names succeeded */
	{
		closedir(d);
		free_names(names, count);
		return (1);
	}
	closedir(d);
	sort_names(names, count);
	print_names(names, count);
	free_names(names, count);

	return (0);
}
