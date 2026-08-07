#include "hls.h"

/**
 * print_permissions - Print file type and permissions
 * @mode: mode returned by lstat
 */
void print_permissions(mode_t mode)
{
	char permissions[11];

	if (S_ISREG(mode))
		permissions[0] = '-';
	else if (S_ISDIR(mode))
		permissions[0] = 'd';
	else if (S_ISLNK(mode))
		permissions[0] = 'l';
	else
		permissions[0] = '?';

	permissions[1] = (mode & S_IRUSR) ? 'r' : '-';
	permissions[2] = (mode & S_IWUSR) ? 'w' : '-';
	permissions[3] = (mode & S_IXUSR) ? 'x' : '-';
	permissions[4] = (mode & S_IRGRP) ? 'r' : '-';
	permissions[5] = (mode & S_IWGRP) ? 'w' : '-';
	permissions[6] = (mode & S_IXGRP) ? 'x' : '-';
	permissions[7] = (mode & S_IROTH) ? 'r' : '-';
	permissions[8] = (mode & S_IWOTH) ? 'w' : '-';
	permissions[9] = (mode & S_IXOTH) ? 'x' : '-';
	permissions[10] = '\0';

	printf("%s", permissions);
}

/**
 * print_owner - Print file owner
 * @st: file information
 */
void print_owner(struct stat *st)
{
	struct passwd *pw;

	pw = getpwuid(st->st_uid);
	if (pw != NULL)
		printf(" %s", pw->pw_name);
	else
		printf(" %u", st->st_uid);
}

/**
 * print_group - Print file group
 * @st: file information
 */
void print_group(struct stat *st)
{
	struct group *gr;

	gr = getgrgid(st->st_gid);
	if (gr != NULL)
		printf(" %s", gr->gr_name);
	else
		printf(" %u", st->st_gid);
}

/**
 * print_date - Print modification date
 * @st: file information
 */
void print_date(struct stat *st)
{
	char *date;

	date = ctime(&st->st_mtime);
	if (date != NULL)
		printf(" %.12s", date + 4);
}

/**
 * print_link - Print symbolic link target
 * @path: directory path
 * @name: link name
 * @mode: file mode
 */
void print_link(const char *path, const char *name, mode_t mode)
{
	char full_path[4096];
	char target[4096];
	ssize_t len;

	if (!S_ISLNK(mode))
		return;

	sprintf(full_path, "%s/%s", path, name);
	len = readlink(full_path, target, sizeof(target) - 1);
	if (len == -1)
		return;

	target[len] = '\0';
	printf(" -> %s", target);
}

/**
 * print_stat_data - Print common stat information
 * @st: file information
 */
void print_stat_data(struct stat *st)
{
	print_permissions(st->st_mode);
	printf(" %lu", (unsigned long)st->st_nlink);
	print_owner(st);
	print_group(st);
	printf(" %lld", (long long)st->st_size);
	print_date(st);
}

/**
 * print_long_path - Print a direct path in long format
 * @path: file path
 */
void print_long_path(const char *path)
{
	struct stat st;

	if (lstat(path, &st) == -1)
		return;

	print_stat_data(&st);
	printf(" %s", path);
	printf("\n");
}
