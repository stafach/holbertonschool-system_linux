#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int count_entries(DIR *d);
int fill_names(DIR *d, char **names);

int my_strlen(const char *s);
char *my_strdup(const char *src);
int my_strcasecmp(const char *s1, const char *s2);

void sort_names(char **names, int count);
void print_names(char **names, int count);
void free_names(char **names, int count);

int list_directory(const char *path, const char *prog);
#endif
