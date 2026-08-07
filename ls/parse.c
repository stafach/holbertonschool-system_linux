#include "hls.h"

/**
 * parse_flag_argument - Parse all flags from one argument
 * @arg: argument containing flags
 * @opts: program options
 * Return: 0 on success, 1 on invalid flag
 */
int parse_flag_argument(const char *arg, options *opts)
{
	int i;

	for (i = 1; arg[i] != '\0'; i++)
	{
		if (handle_flag(arg[i], opts) != 0)
			return (1);
	}

	return (0);
}

/**
 * parse_args - Parse flags and collect paths
 * @argc: argument count
 * @argv: argument vector
 * @opts: program options
 * @paths: array receiving paths
 * Return: number of paths, or -1 on error
 */
int parse_args(int argc, char **argv, options *opts, char ***paths)
{
	char **result;
	int i;
	int count = 0;

	result = malloc(sizeof(char *) * argc);
	if (result == NULL)
		return (-1);

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if (argv[i][1] == '-' && argv[i][2] == '\0')
				continue;

			if (parse_flag_argument(argv[i], opts) != 0)
			{
				free(result);
				fprintf(stderr, "%s: invalid option -- '%s'\n",
					argv[0], argv[i]);
				return (-1);
			}
		}
		else
		{
			result[count] = argv[i];
			count++;
		}
	}

	if (count == 0)
		result[count++] = ".";

	*paths = result;
	return (count);
}
