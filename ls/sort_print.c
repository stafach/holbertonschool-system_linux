#include "hls.h"

/**
 * sort_names - Sort names alphabetically
 * @names: array of names
 * @count: number of elements
 */
void sort_names(char **names, int count)
{
	int i;
	int j;
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
 * print_normal - Print names according to -1
 * @names: array of names
 * @count: number of elements
 * @opts: program options
 */
void print_normal(char **names, int count, options *opts)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("%s", names[i]);
		if (opts->one || i == count - 1)
			printf("\n");
		else
			printf("  ");
	}
}

/**
 * print_names - Print names according to options
 * @names: array of names
 * @count: number of elements
 * @path: directory path
 * @opts: program options
 */
void print_names(char **names, int count,
		const char *path, options *opts)
{
	int i;

	if (!opts->long_format)
	{
		print_normal(names, count, opts);
		return;
	}

	for (i = 0; i < count; i++)
		print_long(path, names[i]);
}

/**
 * free_names - Free names array
 * @names: array of names
 * @count: number of elements
 */
void free_names(char **names, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(names[i]);

	free(names);
}
