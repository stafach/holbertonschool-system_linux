#include <stdio.h>
#include <elf.h>
#include "elf_header.h"

/**
 * print_magic - prints the ELF magic
 * @ident: ELF identification
 */
void print_magic(unsigned char *ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", ident[i]);
	printf("\n");
}

/**
 * print_class - prints the ELF class
 * @class: ELF class
 */
void print_class(unsigned char class)
{
	printf("  Class:                             ");
	if (class == ELFCLASS32)
		printf("ELF32\n");
	else if (class == ELFCLASS64)
		printf("ELF64\n");
	else if (class == ELFCLASSNONE)
		printf("none\n");
	else
		printf("<unknown: %x>\n", class);
}

/**
 * print_data - prints the ELF data encoding
 * @data: ELF data encoding
 */
void print_data(unsigned char data)
{
	printf("  Data:                              ");
	if (data == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (data == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else if (data == ELFDATANONE)
		printf("none\n");
	else
		printf("<unknown: %x>\n", data);
}

/**
 * print_version - prints the ELF identification version
 * @version: ELF version
 */
void print_version(unsigned char version)
{
	printf("  Version:                           %u", version);
	if (version == EV_CURRENT)
		printf(" (current)\n");
	else if (version != EV_NONE)
		printf(" <unknown>\n");
	else
		printf("\n");
}

/**
 * print_osabi - prints the ELF OS ABI
 * @osabi: ELF OS ABI
 */
void print_osabi(unsigned char osabi)
{
	static const char * const names[] = {
		"UNIX - System V", "UNIX - HP-UX", "UNIX - NetBSD",
		"UNIX - Linux", "UNIX - GNU Hurd", NULL, "UNIX - Solaris",
		"UNIX - AIX", "UNIX - IRIX", "UNIX - FreeBSD", "UNIX - TRU64",
		"Novell - Modesto", "UNIX - OpenBSD"
	};

	printf("  OS/ABI:                            ");
	if (osabi < sizeof(names) / sizeof(names[0]) && names[osabi])
		printf("%s\n", names[osabi]);
	else if (osabi == ELFOSABI_ARM)
		printf("ARM\n");
	else if (osabi == ELFOSABI_STANDALONE)
		printf("Standalone App\n");
	else
		printf("<unknown: %x>\n", osabi);
}
