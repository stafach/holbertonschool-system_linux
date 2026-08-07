#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>


/**
 * struct options - Options activated by command line flags
 * @long_format: activate -l
 * @all: activate -a
 */
typedef struct options
{
	int long_format;
	int all;
} options;


/**
 * struct flag - Associates a flag with its handler
 * @str: flag character
 * @f: function handling the flag
 */
typedef struct flag
{
	char *str;
	int (*f)(options *opts);
} flag;


int count_entries(DIR *d);
int fill_names(DIR *d, char **names);

int my_strlen(const char *s);
char *my_strdup(const char *src);
int my_strcasecmp(const char *s1, const char *s2);
const char *my_strerror(int err);

void sort_names(char **names, int count);
void print_names(char **names, int count, const char *path, options *opts);
void free_names(char **names, int count);

int list_directory(const char *path, const char *prog, int show_header);
int check_stat(const char *path, const char *prog);

int flag_l(options *opts);
int flag_a(options *opts);
int handle_flag(char c, options *opts);
int parse_options(int argc, char **argv, options *opts, int *first_path);

void print_permissions(mode_t mode);
void print_long(const char *path, const char *name);

#endif
