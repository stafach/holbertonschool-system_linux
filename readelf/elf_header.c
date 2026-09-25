#include <stdio.h>
#include <elf.h>
#include "elf_header.h"

/**
 * print_magic - prints the ELF magic
 * @ident: ELF identification
 */
static void print_magic(unsigned char *ident)
{
	int i;

	printf("Magic: ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x%s", ident[i], i == EI_NIDENT - 1 ? "\n" : " ");
}

/**
 * print_class - prints the ELF class
 * @class: ELF class
 */
static void print_class(unsigned char class)
{
	printf("Class: ");

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
static void print_data(unsigned char data)
{
	printf("Data: ");

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
static void print_version(unsigned char version)
{
	printf("Version: %u (%s)\n", version,
	       version == EV_CURRENT ? "current" : "unknown");
}

/**
 * print_osabi - prints the ELF OS ABI
 * @osabi: ELF OS ABI
 */
static void print_osabi(unsigned char osabi)
{
	printf("OS/ABI: ");

	switch (osabi)
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
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
static void print_type(unsigned short type)
{
	printf("Type: ");

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
		printf("DYN (Shared object file)\n");
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
static void print_machine(unsigned short machine)
{
	printf("Machine: ");

	switch (machine)
	{
	case EM_386:
		printf("Intel 80386\n");
		break;
	case EM_X86_64:
		printf("Advanced Micro Devices X86-64\n");
		break;
	case EM_ARM:
		printf("ARM\n");
		break;
	case EM_AARCH64:
		printf("AArch64\n");
		break;
	default:
		printf("Unknown\n");
	}
}

/**
 * print_common - prints common ELF header fields
 * @ident: ELF identification
 * @type: ELF type
 * @machine: ELF machine
 * @version: ELF version
 */
static void print_common(unsigned char *ident, unsigned short type,
			 unsigned short machine, unsigned int version)
{
	print_magic(ident);
	print_class(ident[EI_CLASS]);
	print_data(ident[EI_DATA]);
	print_version(ident[EI_VERSION]);
	print_osabi(ident[EI_OSABI]);
	printf("ABI Version: %u\n", ident[EI_ABIVERSION]);
	print_type(type);
	print_machine(machine);
	printf("Version:                           0x%x\n", version);
}

/**
 * print_header32 - prints an ELF32 header
 * @header: ELF32 header
 */
void print_header32(Elf32_Ehdr *header)
{
	printf("ELF Header:\n");
	print_common(header->e_ident, header->e_type,
		     header->e_machine, header->e_version);
	printf("Entry point address:               0x%x\n", header->e_entry);
	printf("Start of program headers:          %u (bytes into file)\n",
	       header->e_phoff);
	printf("Start of section headers:          %u (bytes into file)\n",
	       header->e_shoff);
	printf("Flags:                             0x%x\n", header->e_flags);
	printf("Size of this header:               %u (bytes)\n",
	       header->e_ehsize);
	printf("Size of program headers:           %u (bytes)\n",
	       header->e_phentsize);
	printf("Number of program headers:         %u\n",
	       header->e_phnum);
	printf("Size of section headers:           %u (bytes)\n",
	       header->e_shentsize);
	printf("Number of section headers:         %u\n",
	       header->e_shnum);
	printf("Section header string table index: %u\n",
	       header->e_shstrndx);
}

/**
 * print_header64 - prints an ELF64 header
 * @header: ELF64 header
 */
void print_header64(Elf64_Ehdr *header)
{
	printf("ELF Header:\n");
	print_common(header->e_ident, header->e_type,
		     header->e_machine, header->e_version);
	printf("Entry point address:               0x%lx\n",
	       header->e_entry);
	printf("Start of program headers:          %lu (bytes into file)\n",
	       header->e_phoff);
	printf("Start of section headers:          %lu (bytes into file)\n",
	       header->e_shoff);
	printf("Flags:                             0x%x\n", header->e_flags);
	printf("Size of this header:               %u (bytes)\n",
	       header->e_ehsize);
	printf("Size of program headers:           %u (bytes)\n",
	       header->e_phentsize);
	printf("Number of program headers:         %u\n",
	       header->e_phnum);
	printf("Size of section headers:           %u (bytes)\n",
	       header->e_shentsize);
	printf("Number of section headers:         %u\n",
	       header->e_shnum);
	printf("Section header string table index: %u\n",
	       header->e_shstrndx);
}
