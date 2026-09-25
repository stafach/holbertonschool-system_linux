#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include "elf_header.h"

/**
 * is_elf - checks the ELF magic number
 * @ident: ELF identification
 *
 * Return: 1 if the file is an ELF file, 0 otherwise
 */
static int is_elf(unsigned char *ident)
{
	return (ident[EI_MAG0] == ELFMAG0 && ident[EI_MAG1] == ELFMAG1 &&
		ident[EI_MAG2] == ELFMAG2 && ident[EI_MAG3] == ELFMAG3);
}

/**
 * handle32 - reads, converts and prints an ELF32 header
 * @fd: file descriptor
 *
 * Return: 0 on success, 1 on error
 */
static int handle32(int fd)
{
	Elf32_Ehdr header;

	if (lseek(fd, 0, SEEK_SET) == -1 ||
	    read(fd, &header, sizeof(header)) != (ssize_t)sizeof(header))
	{
		fprintf(stderr, "Error reading file\n");
		return (1);
	}
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		swap_header32(&header);
	print_header32(&header);
	return (0);
}

/**
 * handle64 - reads, converts and prints an ELF64 header
 * @fd: file descriptor
 *
 * Return: 0 on success, 1 on error
 */
static int handle64(int fd)
{
	Elf64_Ehdr header;

	if (lseek(fd, 0, SEEK_SET) == -1 ||
	    read(fd, &header, sizeof(header)) != (ssize_t)sizeof(header))
	{
		fprintf(stderr, "Error reading file\n");
		return (1);
	}
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		swap_header64(&header);
	print_header64(&header);
	return (0);
}

/**
 * main - displays the ELF header of a file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	int fd, ret;
	unsigned char ident[EI_NIDENT];

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
	if (read(fd, ident, EI_NIDENT) != EI_NIDENT || !is_elf(ident))
	{
		fprintf(stderr, "Error: Not an ELF file\n");
		close(fd);
		return (1);
	}
	if (ident[EI_CLASS] == ELFCLASS32)
		ret = handle32(fd);
	else if (ident[EI_CLASS] == ELFCLASS64)
		ret = handle64(fd);
	else
	{
		fprintf(stderr, "Error: Invalid ELF class\n");
		ret = 1;
	}
	close(fd);
	return (ret);
}
