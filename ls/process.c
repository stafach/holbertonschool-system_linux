#include "hls.h"

/**
 * collect_errors - Check all paths and store errors
 * @paths: paths to check
 * @count: number of paths
 * @statuses: status of each path
 * @errors: array receiving errors
 * Return: number of errors
 */
int collect_errors(char **paths, int count,
		int *statuses, path_error *errors)
{
	int i;
	int error;
	int error_count = 0;

	for (i = 0; i < count; i++)
	{
		statuses[i] = check_stat(paths[i], &error);
		if (statuses[i] == 2)
		{
			errors[error_count].path = paths[i];
			errors[error_count].error = error;
			error_count++;
		}
	}

	return (error_count);
}

/**
 * print_errors - Print all stored errors
 * @errors: stored errors
 * @count: number of errors
 * @prog: program name
 */
void print_errors(path_error *errors, int count, const char *prog)
{
	int i;

	for (i = 0; i < count; i++)
	{
		fprintf(stderr, "%s: cannot access %s: %s\n",
			prog, errors[i].path,
			my_strerror(errors[i].error));
	}
}

/**
 * process_valid_paths - Display all valid paths
 * @paths: paths to process
 * @statuses: status of each path
 * @count: number of paths
 * @prog: program name
 * @opts: program options
 * Return: program status
 */
int process_valid_paths(char **paths, int *statuses,
		int count, const char *prog, options *opts)
{
	int i;
	int ret;
	int status = 0;
	int printed = 0;

	for (i = 0; i < count; i++)
	{
		if (statuses[i] == 2)
			continue;

		if (printed)
			printf("\n");

		ret = list_directory(paths[i], prog, count > 1, opts);
		if (ret > status)
			status = ret;

		printed = 1;
	}

	return (status);
}
