#include "hls.h"

/**
* count_entries - Count non-hidden entries in a directory
* @d: opened directory stream
* @opts: program options
* Return: number of entries found
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
* fill_names - Read directory entries into a names array
* @d: opened directory stream
* @names: pre-allocated array to fill
* @opts: program options
* Return: 0 if all good or 1 if error
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
				return (1);
			i++;
		}
	}
	return (0);
}


/**
 * open_and_fill - Open directory and fill names
 * @path: directory path
 * @names: array to fill
 * @opts: program options
 * Return: 0 on success, 1 on error
 */
int open_and_fill(const char *path, char **names, options *opts)
{
	DIR *d;
	int ret;

	d = opendir(path);
	if (d == NULL)
		return (1);

	ret = fill_names(d, names, opts);
	closedir(d);

	return (ret);
}


/**
* list_directory - List content of a single directory
* @path: path of the directory to list
* @prog: program name (argv[0]), used for error messages
* @show_header: whether to show the header
* @opts: program options
* Return: 0 on success, 1 or 2 on error
*/

int list_directory(const char *path, const char *prog,
	int show_header, options *opts)
{
	DIR *d;
	char **names;
	int count;

	if (check_stat(path, prog) == 0)
	{
		d = opendir(path);
		if (d == NULL)
		{
			fprintf(stderr, "%s: cannot access %s: %s",
				prog, path, my_strerror(errno));
			return (1);
		}
		if (show_header)
			printf("%s:\n", path);
		count = count_entries(d, opts);
		closedir(d);
		names = malloc(sizeof(char *) * count);
		if (names == NULL)
			return (1);
		d = opendir(path);
		if (d == NULL)
		{
			free(names);
			return (2);
		}
		if (open_and_fill(path, names, opts) != 0)
		{
			closedir(d);
			free_names(names, count);
			return (1);
		}
		closedir(d);
		sort_names(names, count);
		print_names(names, count, path, opts);
		free_names(names, count);
		return (0);
	}
	return (1);
}

/**
* check_stat - Check the status of a file or directory
* @path: path to the file or directory
* @prog: program name (argv[0]), used for error messages
* Return: 0 if all good, 1 if not found, 2 if not a directory
*/

int check_stat(const char *path, const char *prog)
{
	struct stat st;

	if (lstat(path, &st) == -1)
	{
		fprintf(stderr, "%s: cannot access %s: %s\n",
			prog, path, my_strerror(errno));
		return (2);
	}
	if (!S_ISDIR(st.st_mode))
	{
		printf("%s\n", path);
		return (1);
	}
	return (0);
}
