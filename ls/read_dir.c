#include "hls.h"

/**
 * count_entries - Count directory entries
 * @d: opened directory stream
 * @opts: program options
 * Return: number of entries
 */
int count_entries(DIR *d, options *opts)
{
	struct dirent *dir;
	int count = 0;

	while ((dir = readdir(d)) != NULL)
	{
		if (opts->all || dir->d_name[0] != '.')
			count++;
	}

	return (count);
}

/**
 * free_partial_names - Free names allocated before an error
 * @names: names array
 * @count: number of allocated names
 */
void free_partial_names(char **names, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(names[i]);
}

/**
 * fill_names - Fill an array with directory entry names
 * @d: opened directory stream
 * @names: array to fill
 * @opts: program options
 * Return: number filled, or -1 on allocation failure
 */
int fill_names(DIR *d, char **names, options *opts)
{
	struct dirent *dir;
	int i = 0;

	while ((dir = readdir(d)) != NULL)
	{
		if (opts->all || dir->d_name[0] != '.')
		{
			names[i] = my_strdup(dir->d_name);
			if (names[i] == NULL)
			{
				free_partial_names(names, i);
				return (-1);
			}
			i++;
		}
	}

	return (i);
}

/**
 * open_and_fill - Open directory and fill names
 * @path: directory path
 * @names: array to fill
 * @opts: program options
 * Return: number of names, or -1 on error
 */
int open_and_fill(const char *path, char **names, options *opts)
{
	DIR *d;
	int ret;

	d = opendir(path);
	if (d == NULL)
		return (-1);

	ret = fill_names(d, names, opts);
	closedir(d);

	return (ret);
}

/**
 * print_file - Print a file passed directly
 * @path: file path
 * @opts: program options
 */
void print_file(const char *path, options *opts)
{
	if (opts->long_format)
		print_long_path(path);
	else
		printf("%s\n", path);
}

/**
 * list_directory - List content of a path
 * @path: path to list
 * @prog: program name
 * @show_header: whether to print header
 * @opts: program options
 * Return: 0 on success, 1 or 2 on error
 */
int list_directory(const char *path, const char *prog,
		int show_header, options *opts)
{
	DIR *d;
	char **names;
	int count;
	int filled;
	int status;

	(void)prog;
	status = check_stat(path, &filled);
	if (status == 1)
	{
		print_file(path, opts);
		return (0);
	}
	if (status == 2)
		return (2);

	d = opendir(path);
	if (d == NULL)
		return (2);

	if (show_header)
		printf("%s:\n", path);

	count = count_entries(d, opts);
	closedir(d);

	if (count == 0)
		return (0);

	names = malloc(sizeof(char *) * count);
	if (names == NULL)
		return (1);

	filled = open_and_fill(path, names, opts);
	if (filled < 0)
	{
		free(names);
		return (1);
	}

	sort_names(names, filled);
	print_names(names, filled, path, opts);
	free_names(names, filled);

	return (0);
}

/**
 * check_stat - Check a path without printing errors
 * @path: path to check
 * @error: receives errno on error
 * Return: 0 directory, 1 file, 2 error
 */
int check_stat(const char *path, int *error)
{
	struct stat st;
	DIR *d;

	if (lstat(path, &st) == -1)
	{
		*error = errno;
		return (2);
	}

	if (!S_ISDIR(st.st_mode))
		return (1);

	d = opendir(path);
	if (d == NULL)
	{
		*error = errno;
		return (2);
	}

	closedir(d);
	return (0);
}
