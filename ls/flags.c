#include "hls.h"

/**
 * flag_l - Activate long format
 * @opts: program options
 * Return: 0 on success
 */
int flag_l(options *opts)
{
	opts->long_format = 1;
	return (0);
}

/**
 * flag_a - Activate all files
 * @opts: program options
 * Return: 0 on success
 */
int flag_a(options *opts)
{
	opts->all = 1;
	return (0);
}


/**
 * handle_flag - Find and execute a flag handler
 * @c: flag character
 * @opts: program options
 * Return: 0 on success, 1 if flag is unknown
 */
int handle_flag(char c, options *opts)
{
	int i;

	static flag flags[] = {
	{"l", flag_l},
	{"a", flag_a},
	{NULL, NULL}
};

	for (i = 0; flags[i].str != NULL; i++)
	{
		if (flags[i].str[0] == c)
			return (flags[i].f(opts));
	}

	return (1);
}

/**
 * parse_options - Parse command line options
 * @argc: argument count
 * @argv: argument vector
 * @opts: program options
 * @first_path: index of first path argument
 * Return: 0 on success, 1 on invalid option
 */
int parse_options(int argc, char **argv, options *opts, int *first_path)
{
	int i, j;

	*first_path = 1;

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-' || argv[i][1] == '\0')
			break;

		for (j = 1; argv[i][j] != '\0'; j++)
		{
			if (handle_flag(argv[i][j], opts) != 0)
			{
				fprintf(stderr, "%s: invalid option -- '%c'\n",
					argv[0], argv[i][j]);
				return (1);
			}
		}

		*first_path = i + 1;
	}

	return (0);
}

