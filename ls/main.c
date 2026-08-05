#include "hls.h"

/**
* main - Entry point
* @argc: argument count
* @argv: argument vector
* Return: 0 on success, 1 or 2 on error
*/

int main(int argc, char **argv)
{
	int i, ret, status, count;
	char **names;

	status = 0;
	if (argc == 1)
		return (list_directory(".", argv[0], 0));

	count = argc - 1;
	names = malloc(sizeof(char *) * count);
	if (names == NULL)
		return (1);

	for (i = 0; i < count; i++)
		names[i] = argv[i + 1];
	sort_names(names, count);
	for (i = 0; i < count; i++)
	{
		if (i > 0)
			printf("\n");
		ret = list_directory(names[i], argv[0], count > 1);
		if (ret > status)
			status = ret;
	}
	free(names);
	return (status);
}
