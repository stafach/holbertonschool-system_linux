#include "_getline.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * append_char - adds a character to a string
 * @line: current string
 * @len: current length
 * @c: character to add
 *
 * Return: new string or NULL
 */
char *append_char(char *line, size_t *len, char c)
{
	char *tmp;

	tmp = realloc(line, *len + 2);
	if (tmp == NULL)
	{
		free(line);
		return (NULL);
	}

	tmp[*len] = c;
	(*len)++;
	tmp[*len] = '\0';

	return (tmp);
}

/**
 * fill_buffer - reads data into buffer
 * @fd: file descriptor
 * @buffer: buffer to fill
 *
 * Return: number of bytes read or -1
 */
ssize_t fill_buffer(int fd, char *buffer)
{
	ssize_t size;

	size = read(fd, buffer, READ_SIZE);
	if (size > 0)
		buffer[size] = '\0';

	return (size);
}

/**
 * empty_line - creates an empty string
 *
 * Return: empty string or NULL
 */
char *empty_line(void)
{
	char *line;

	line = malloc(1);
	if (line == NULL)
		return (NULL);

	line[0] = '\0';
	return (line);
}

/**
* initialize_buffer - initializes the buffer
* @buffer: the buffer
* @pos: the position in the buffer
* @size: the size of the buffer
* Return: Null if malloc error
*/
void initialize_buffer(char **buffer, size_t *pos, ssize_t *size)
{
	*buffer = malloc(READ_SIZE + 1);
	if (*buffer == NULL)
		return;
	*pos = 0;
	*size = 0;
}

/**
 * _getline - reads a line from a file descriptor
 * @fd: file descriptor
 *
 * Return: line without newline or NULL
 */
char *_getline(const int fd)
{
	static char *buffer;
	static size_t pos;
	static ssize_t size;
	char *line;
	size_t len;

	if (buffer == NULL)
	{
		initialize_buffer(&buffer, &pos, &size);
	}

	line = NULL;
	len = 0;

	while (1)
	{
		if (pos >= (size_t)size)
		{
			size = fill_buffer(fd, buffer);
			pos = 0;
			if (size <= 0)
			{
				free(buffer);
				buffer = NULL;
				return (line);
			}
		}

		while (pos < (size_t)size && buffer[pos] != '\n')
		{
			line = append_char(line, &len, buffer[pos]);
			if (line == NULL)
				return (NULL);
			pos++;
		}

		if (pos < (size_t)size && buffer[pos] == '\n')
		{
			pos++;
			if (line == NULL)
				return (empty_line());
			return (line);
		}
	}
}
