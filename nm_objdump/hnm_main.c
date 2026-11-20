#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "Hnm.h"

/**
 * read_file - read a whole file into a newly allocated buffer
 * @prog: program name
 * @name: path of the file
 * @size: where to store the size of the file
 *
 * Return: the buffer (to free), or NULL on error (message printed)
 */
static unsigned char *read_file(const char *prog, const char *name,
				size_t *size)
{
	struct stat st;
	FILE *fp;
	unsigned char *buf;

	if (stat(name, &st) == -1)
	{
		if (errno == ENOENT)
			fprintf(stderr, "%s: '%s': No such file\n", prog, name);
		else
			fprintf(stderr, "%s: %s: %s\n", prog, name, strerror(errno));
		return (NULL);
	}
	if (S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Warning: '%s' is a directory\n", prog, name);
		return (NULL);
	}
	if (!S_ISREG(st.st_mode))
	{
		fprintf(stderr, "%s: Warning: '%s' is not an ordinary file\n",
			prog, name);
		return (NULL);
	}
	fp = fopen(name, "rb");
	if (!fp)
	{
		fprintf(stderr, "%s: %s: %s\n", prog, name, strerror(errno));
		return (NULL);
	}
	buf = malloc(st.st_size ? st.st_size : 1);
	if (buf)
		*size = fread(buf, 1, st.st_size, fp);
	fclose(fp);
	return (buf);
}

/**
 * process_elf - list the symbols of an ELF image held in memory
 * @prog: program name
 * @name: name to display
 * @data: contents of the ELF file
 * @size: size of the contents
 * @header: non zero to print the "\nname:\n" header line
 *
 * Return: 0 on success, 1 on error
 */
int process_elf(const char *prog, const char *name,
		const unsigned char *data, size_t size, int header)
{
	elf_file_t ef;

	memset(&ef, 0, sizeof(ef));
	ef.prog = prog;
	ef.name = name;
	ef.data = data;
	ef.size = size;
	if (check_elf(&ef) == -1)
	{
		fflush(stdout);
		fprintf(stderr, "%s: %s: file format not recognized\n",
			prog, name);
		return (header != 2);
	}
	if (header)
		printf("\n%s:\n", name);
	return (print_symbols(&ef));
}

/**
 * process_file - list the symbols of one object file or archive
 * @prog: program name
 * @name: path of the file
 * @multi: non zero if several files are given
 *
 * Return: 0 on success, 1 on error
 */
static int process_file(const char *prog, const char *name, int multi)
{
	unsigned char *buf;
	size_t size = 0;
	int ret;

	fflush(stdout);
	buf = read_file(prog, name, &size);
	if (!buf)
		return (1);
	if (is_archive(buf, size))
	{
		if (multi)
			printf("\n%s:\n", name);
		ret = process_archive(prog, buf, size);
	}
	else
	{
		ret = process_elf(prog, name, buf, size, multi);
	}
	free(buf);
	return (ret);
}

/**
 * main - entry point, reproduces `nm -p`
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: EXIT_SUCCESS, or EXIT_FAILURE if an error occurred
 */
int main(int argc, char **argv)
{
	int i, ret = 0;

	if (argc < 2)
		return (process_file(argv[0], "a.out", 0) ?
			EXIT_FAILURE : EXIT_SUCCESS);
	for (i = 1; i < argc; i++)
		ret |= process_file(argv[0], argv[i], argc > 2);
	return (ret ? EXIT_FAILURE : EXIT_SUCCESS);
}
