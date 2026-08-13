#ifndef _GETLINE_H
#define _GETLINE_H

#include <stddef.h>
#include <sys/types.h>

#define READ_SIZE 1024

char *_getline(const int fd);
char *append_char(char *line, size_t *len, char c);
ssize_t fill_buffer(int fd, char *buffer);
char *empty_line(void);
void initialize_buffer(char **buffer, size_t *pos, ssize_t *size);

#endif
