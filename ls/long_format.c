#include "hls.h"

/**
 * print_long - Print file in long format
 * @path: directory path
 * @name: file name
 */
void print_long(const char *path, const char *name)
{
	struct stat st;
	char full_path[4096];
	char *date;

	sprintf(full_path, "%s/%s", path, name);

	if (lstat(full_path, &st) == -1)
		return;

	print_permissions(st.st_mode);
	printf(" %lu", (unsigned long)st.st_nlink);
	print_owner(&st);
	print_group(&st);
	printf(" %lld", (long long)st.st_size);

	date = ctime(&st.st_mtime);
	if (date != NULL)
		printf(" %.6s %.4s", date + 4, date + 20);

	printf(" %s", name);
	print_link(path, name, st.st_mode);
	printf("\n");
}
