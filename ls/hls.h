#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int count_entries(DIR *d);
int fill_names(DIR *d, char **names);

int my_strlen(const char *s);
char *my_strdup(const char *src);
int my_strcasecmp(const char *s1, const char *s2);
const char *my_strerror(int err);

void sort_names(char **names, int count);
void print_names(char **names, int count);
void free_names(char **names, int count);

int list_directory(const char *path, const char *prog, int show_header);
int check_stat(const char *path, const char *prog);
#endif
