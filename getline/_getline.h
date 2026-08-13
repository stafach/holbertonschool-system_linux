#ifndef _GETLINE_H
#define _GETLINE_H

#include <stddef.h>
#include <sys/types.h>

#define READ_SIZE 1024

struct buffer_state
{
	char *buffer;
	size_t pos;
	ssize_t size;
};

char *_getline(const int fd);
char *append_char(char *line, size_t *len, char c);
ssize_t fill_buffer(int fd, char *buffer);
char *empty_line(void);
void initialize_buffer(struct buffer_state *state);
void free_states(struct buffer_state *states);

#endif
