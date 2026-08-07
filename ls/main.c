#include "hls.h"

/**
 * init_options - Initialize program options
 * @opts: program options
 */
void init_options(options *opts)
{
	opts->one = 0;
	opts->long_format = 0;
	opts->all = 0;
}

/**
 * process_paths - Check errors before displaying valid paths
 * @paths: paths to process
 * @count: number of paths
 * @prog: program name
 * @opts: program options
 * Return: program status
 */
int process_paths(char **paths, int count,
		const char *prog, options *opts)
{
	int *statuses;
	path_error *errors;
	int error_count;
	int status;

	statuses = malloc(sizeof(int) * count);
	errors = malloc(sizeof(path_error) * count);
	if (statuses == NULL || errors == NULL)
	{
		free(statuses);
		free(errors);
		return (1);
	}

	error_count = collect_errors(paths, count, statuses, errors);
	print_errors(errors, error_count, prog);
	status = process_valid_paths(paths, statuses, count, prog, opts);

	free(statuses);
	free(errors);

	if (error_count > 0)
		return (1);

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
	char **paths;
	int count;
	int status;

	init_options(&opts);
	count = parse_args(argc, argv, &opts, &paths);
	if (count < 0)
		return (1);

	status = process_paths(paths, count, argv[0], &opts);
	free(paths);

	return (status);
}
