#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int compare(const void *a, const void *b);
int read_names(DIR *d, char ***names, int *count);
void print_names(char **names, int count);

#endif /* HLS_H */
