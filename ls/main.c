#include "hls.h"

/**
* main - Entry point
* @argc: argument count
* @argv: argument vector
* Return: 0 on success, 1 or 2 on error
*/

int main(int argc, char **argv)
{
	int i, ret, status;

	status = 0;
	if (argc == 1)
		return (list_directory(".", argv[0]));

	if (argc == 2)
		return (list_directory(argv[1], argv[0]));

	for (i = 1; i < argc; i++)
	{
		printf("%s:\n", argv[i]);
		ret = list_directory(argv[i], argv[0]);
		if (ret > status)
			status = ret;
	}
	return (status);
}
