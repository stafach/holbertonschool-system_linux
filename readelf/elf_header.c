```c
#include <stdio.h>
#include "elf_header.h"

/**
 * print_magic - prints the ELF magic number
 * @ident: ELF identification bytes
 */
void print_magic(unsigned char *ident)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x%s", ident[i], i == EI_NIDENT - 1 ? "\n" : " ");
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
	else
		printf("none\n");
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
	else
		printf("none\n");
}

/**
 * print_version - prints the ELF version
 * @version: ELF version
 */
void print_version(unsigned char version)
{
	printf("  Version:                           %d (%s)\n",
	       version, version == EV_CURRENT ? "current" : "unknown");
}

/**
 * print_osabi - prints the ELF OS/ABI
 * @osabi: ELF OS/ABI
 */
void print_osabi(unsigned char osabi)
{
	printf("  OS/ABI:                            ");

	switch (osabi)
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	default:
		printf("<unknown: %x>\n", osabi);
	}
}

/**
 * print_type - prints the ELF type
 * @type: ELF type
 */
void print_type(unsigned short type)
{
	printf("  Type:                              ");

	switch (type)
	{
	case ET_NONE:
		printf("NONE (No file type)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Position-Independent Executable file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown>\n");
	}
}

/**
 * print_machine - prints the ELF machine
 * @machine: ELF machine
 */
void print_machine(unsigned short machine)
{
	printf("  Machine:                           ");

	switch (machine)
	{
	case EM_X86_64:
		printf("Advanced Micro Devices X86-64\n");
		break;
	case EM_386:
		printf("Intel 80386\n");
		break;
	case EM_AARCH64:
		printf("AArch64\n");
		break;
	case EM_ARM:
		printf("ARM\n");
		break;
	default:
		printf("Unknown\n");
	}
}

/**
 * print_header - prints the ELF header
 * @header: ELF header
 */
void print_header(Elf64_Ehdr *header)
{
	printf("ELF Header:\n");
	print_magic(header->e_ident);
	print_class(header->e_ident[EI_CLASS]);
	print_data(header->e_ident[EI_DATA]);
	print_version(header->e_ident[EI_VERSION]);
	print_osabi(header->e_ident[EI_OSABI]);
	printf("  ABI Version:                       %d\n",
	       header->e_ident[EI_ABIVERSION]);
	print_type(header->e_type);
	print_machine(header->e_machine);
	printf("  Version:                           0x%x\n", header->e_version);
	printf("  Entry point address:               0x%lx\n",
	       header->e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n",
	       header->e_phoff);
	printf("  Start of section headers:          %lu (bytes into file)\n",
	       header->e_shoff);
	printf("  Flags:                             0x%x\n", header->e_flags);
	printf("  Size of this header:               %u (bytes)\n",
	       header->e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n",
	       header->e_phentsize);
	printf("  Number of program headers:         %u\n",
	       header->e_phnum);
	printf("  Size of section headers:           %u (bytes)\n",
	       header->e_shentsize);
	printf("  Number of section headers:         %u\n",
	       header->e_shnum);
	printf("  Section header string table index: %u\n",
	       header->e_shstrndx);
}
