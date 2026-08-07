#ifndef HLS_H
#define HLS_H

#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/**
 * struct options - Options activated by command line flags
 * @one: activate -1
 * @long_format: activate -l
 * @all: activate -a
 * @almost_all: activate -A
 */
typedef struct options
{
	int one;
	int long_format;
	int all;
	int almost_all;
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

/**
 * struct path_error - Stores an error associated with a path
 * @path: path that caused the error
 * @error: errno value
 */
typedef struct path_error
{
	char *path;
	int error;
} path_error;

/* flags.c */
int flag_l(options *opts);
int flag_a(options *opts);
int flag_one(options *opts);
int flag_almost_all(options *opts);
int handle_flag(char c, options *opts);

/* parse.c */
int parse_flag_argument(const char *arg, options *opts);
int parse_args(int argc, char **argv, options *opts, char ***paths);

/* read_dir.c */
int count_entries(DIR *d, options *opts);
int fill_names(DIR *d, char **names, options *opts);
int open_and_fill(const char *path, char **names, options *opts);
int list_directory(const char *path, const char *prog,
		int show_header, options *opts);
int check_stat(const char *path, int *error);

/* sort_print.c */
void sort_names(char **names, int count);
void print_normal(char **names, int count, options *opts);
void print_names(char **names, int count,
		const char *path, options *opts);
void free_names(char **names, int count);

/* str.c */
int my_strlen(const char *s);
char *my_strdup(const char *src);
int my_strcasecmp(const char *s1, const char *s2);
const char *my_strerror(int err);

/* options.c */
void print_permissions(mode_t mode);
void print_owner(struct stat *st);
void print_group(struct stat *st);
void print_date(struct stat *st);
void print_link(const char *path, const char *name, mode_t mode);
void print_long(const char *path, const char *name);
void print_long_path(const char *path);

/* process.c */
int collect_errors(char **paths, int count,
		int *statuses, path_error *errors);
void print_errors(path_error *errors, int count, const char *prog);
int process_valid_paths(char **paths, int *statuses,
		int count, const char *prog, options *opts);

/* main.c */
void init_options(options *opts);
int process_paths(char **paths, int count,
		const char *prog, options *opts);

#endif
