#include "hls.h"

/**
 * my_strlen - Compute the length of a string
 * @s: string to measure
 * Return: length of the string
 */
int my_strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * my_strdup - Allocate and copy a string
 * @src: string to duplicate
 * Return: pointer to new string, or NULL
 */
char *my_strdup(const char *src)
{
	char *dest;
	int len;
	int i;

	len = my_strlen(src);
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * my_strcasecmp - Compare two strings ignoring case
 * @s1: first string
 * @s2: second string
 * Return: difference between first differing characters
 */
int my_strcasecmp(const char *s1, const char *s2)
{
	int i = 0;
	char c1;
	char c2;

	while (s1[i] && s2[i])
	{
		c1 = s1[i];
		c2 = s2[i];

		if (c1 >= 'A' && c1 <= 'Z')
			c1 += 32;
		if (c2 >= 'A' && c2 <= 'Z')
			c2 += 32;

		if (c1 != c2)
			return (c1 - c2);

		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * my_strerror - Return a message matching an errno value
 * @err: errno value
 * Return: error message
 */
const char *my_strerror(int err)
{
	if (err == ENOENT)
		return ("No such file or directory");
	if (err == EACCES)
		return ("Permission denied");
	if (err == ENOTDIR)
		return ("Not a directory");
	if (err == ELOOP)
		return ("Too many levels of symbolic links");
	if (err == ENAMETOOLONG)
		return ("File name too long");

	return ("Unknown error");
}
