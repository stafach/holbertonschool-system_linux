```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include "elf_header.h"

/**
 * main - displays the ELF header
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	int fd;
	Elf64_Ehdr header;
	ssize_t bytes;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}

	bytes = read(fd, &header, sizeof(header));
	if (bytes != sizeof(header))
	{
		fprintf(stderr, "Error reading file\n");
		close(fd);
		return (1);
	}

	if (header.e_ident[EI_MAG0] != ELFMAG0 ||
	    header.e_ident[EI_MAG1] != ELFMAG1 ||
	    header.e_ident[EI_MAG2] != ELFMAG2 ||
	    header.e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Error: Not an ELF file\n");
		close(fd);
		return (1);
	}

	if (header.e_ident[EI_CLASS] != ELFCLASS64)
	{
		fprintf(stderr, "Error: Only ELF64 files are supported\n");
		close(fd);
		return (1);
	}

	print_header(&header);
	close(fd);

	return (0);
}
