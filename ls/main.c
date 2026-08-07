#include "hls.h"

/**
 * init_options - Initialize program options
 * @opts: program options
 */
void init_options(options *opts)
{
	opts->long_format = 0;
	opts->all = 0;
}

/**
 * process_paths - Process all paths given by the user
 * @argc: argument count
 * @argv: argument vector
 * @first_path: index of first path
 * @opts: program options
 * Return: program status
 */
int process_paths(int argc, char **argv,
		int first_path, options *opts)
{
	int i;
	int ret;
	int status = 0;

	for (i = first_path; i < argc; i++)
	{
		if (i > first_path)
			printf("\n");

		ret = list_directory(argv[i], argv[0],
				argc - first_path > 1, opts);

		if (ret > status)
			status = ret;
	}

	return (status);
}

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: program status
 */
int main(int argc, char **argv)
{
	options opts;
	int first_path;

	init_options(&opts);

	if (parse_options(argc, argv, &opts, &first_path) != 0)
		return (1);

	if (first_path >= argc)
		return (list_directory(".", argv[0], 0, &opts));

	return (process_paths(argc, argv, first_path, &opts));
}
