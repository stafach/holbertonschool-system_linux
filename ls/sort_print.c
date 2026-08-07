#include "hls.h"

/**
* sort_names - Sort an array of strings alphabetically (bubble sort)
* @names: array of strings to sort
* @count: number of elements in the array
*/

void sort_names(char **names, int count)
{
	int i, j;
	char *tmp;

	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (my_strcasecmp(names[j], names[j + 1]) > 0)
			{
				tmp = names[j];
				names[j] = names[j + 1];
				names[j + 1] = tmp;
			}
		}
	}
}

/**
* print_names - Print each name on its own line
* @names: array of strings to print
* @count: number of elements in the array
* @path: path of the directory
* @opts: program options
*/

void print_names(char **names, int count, const char *path, options *opts)
{
	int i;


	for (i = 0; i < count - 1; i++)
	{
		if (opts->long_format)
			print_long_format(path, names[i]);
		else
			printf("%s  ", names[i]);
	}
	if (!opts->long_format)
		printf("%s\n", names[count - 1]);
}


/**
* free_names - Free an array of strings and the array itself
* @names: array of strings to free
* @count: number of elements in the array
*/

void free_names(char **names, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(names[i]);
	free(names);
}
