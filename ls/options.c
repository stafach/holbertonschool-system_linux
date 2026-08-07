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
