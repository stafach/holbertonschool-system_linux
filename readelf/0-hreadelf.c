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
	unsigned char ident[EI_NIDENT];
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

	bytes = read(fd, ident, EI_NIDENT);
	if (bytes != EI_NIDENT)
	{
		fprintf(stderr, "Error reading file\n");
		close(fd);
		return (1);
	}

	if (ident[EI_MAG0] != ELFMAG0 ||
	    ident[EI_MAG1] != ELFMAG1 ||
	    ident[EI_MAG2] != ELFMAG2 ||
	    ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Error: Not an ELF file\n");
		close(fd);
		return (1);
	}

	if (ident[EI_CLASS] == ELFCLASS32)
	{
		Elf32_Ehdr header;

		lseek(fd, 0, SEEK_SET);
		if (read(fd, &header, sizeof(header)) != sizeof(header))
		{
			fprintf(stderr, "Error reading file\n");
			close(fd);
			return (1);
		}
		print_header32(&header);
	}
	else if (ident[EI_CLASS] == ELFCLASS64)
	{
		Elf64_Ehdr header;

		lseek(fd, 0, SEEK_SET);
		if (read(fd, &header, sizeof(header)) != sizeof(header))
		{
			fprintf(stderr, "Error reading file\n");
			close(fd);
			return (1);
		}
		print_header64(&header);
	}
	else
	{
		fprintf(stderr, "Error: Invalid ELF class\n");
		close(fd);
		return (1);
	}

	close(fd);
	return (0);
}
