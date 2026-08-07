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
 * flag_one - Activate one file per line
 * @opts: program options
 * Return: 0 on success
 */
int flag_one(options *opts)
{
	opts->one = 1;
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
	{"1", flag_one},
	{NULL, NULL}
};

	for (i = 0; flags[i].str != NULL; i++)
	{
		if (flags[i].str[0] == c)
			return (flags[i].f(opts));
	}

	return (1);
}
