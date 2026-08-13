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
 * initialize_buffer - initializes a buffer state
 * @state: buffer state
 *
 * Return: nothing
 */
void initialize_buffer(struct buffer_state *state)
{
	state->buffer = malloc(READ_SIZE + 1);
	if (state->buffer == NULL)
		return;

	state->pos = 0;
	state->size = 0;
}

/**
 * free_states - frees all buffer states
 * @states: array of buffer states
 *
 * Return: nothing
 */
void free_states(struct buffer_state *states)
{
	int i;

	for (i = 0; i < 1024; i++)
	{
		free(states[i].buffer);
		states[i].buffer = NULL;
		states[i].pos = 0;
		states[i].size = 0;
	}
}

/**
 * _getline - reads a line from a file descriptor
 * @fd: file descriptor
 *
 * Return: line without newline or NULL
 */
char *_getline(const int fd)
{
	static struct buffer_state states[1024];
	struct buffer_state *state;
	char *line;
	size_t len;

	if (fd == -1)
	{
		free_states(states);
		return (NULL);
	}

	if (fd < 0 || fd >= 1024)
		return (NULL);

	state = &states[fd];

	if (state->buffer == NULL)
		initialize_buffer(state);

	if (state->buffer == NULL)
		return (NULL);

	line = NULL;
	len = 0;

	while (1)
	{
		if (state->pos >= (size_t)state->size)
		{
			state->size = fill_buffer(fd, state->buffer);
			state->pos = 0;

			if (state->size <= 0)
			{
				free(state->buffer);
				state->buffer = NULL;
				return (line);
			}
		}

		while (state->pos < (size_t)state->size &&
		       state->buffer[state->pos] != '\n')
		{
			line = append_char(line, &len, state->buffer[state->pos]);
			if (line == NULL)
				return (NULL);
			state->pos++;
		}

		if (state->pos < (size_t)state->size &&
		    state->buffer[state->pos] == '\n')
		{
			state->pos++;
			if (line == NULL)
				return (empty_line());
			return (line);
		}
	}
}
