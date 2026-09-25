#include <stdio.h>
#include <elf.h>
#include "elf_header.h"

/**
 * print_type - prints the ELF file type
 * @type: ELF type
 */
void print_type(unsigned short type)
{
	printf("  Type:                              ");
	if (type == ET_NONE)
		printf("NONE (None)\n");
	else if (type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (type == ET_CORE)
		printf("CORE (Core file)\n");
	else if (type >= ET_LOPROC)
		printf("Processor Specific: (%x)\n", type);
	else if (type >= ET_LOOS && type <= ET_HIOS)
		printf("OS Specific: (%x)\n", type);
	else
		printf("<unknown>: %x\n", type);
}

/**
 * print_machine - prints the ELF target machine
 * @machine: ELF machine
 */
void print_machine(unsigned short machine)
{
	static const struct
	{
		unsigned short id;
		const char *name;
	} machines[] = {
		{EM_NONE, "None"}, {EM_M32, "WE32100"}, {EM_SPARC, "Sparc"},
		{EM_386, "Intel 80386"}, {EM_68K, "MC68000"},
		{EM_88K, "MC88000"}, {EM_860, "Intel 80860"},
		{EM_MIPS, "MIPS R3000"}, {EM_PARISC, "HPPA"},
		{EM_SPARC32PLUS, "Sparc v8+"}, {EM_PPC, "PowerPC"},
		{EM_PPC64, "PowerPC64"}, {EM_S390, "IBM S/390"},
		{EM_ARM, "ARM"}, {EM_SH, "Renesas / SuperH SH"},
		{EM_SPARCV9, "Sparc v9"}, {EM_IA_64, "Intel IA-64"},
		{EM_X86_64, "Advanced Micro Devices X86-64"},
		{EM_AARCH64, "AArch64"}
	};
	unsigned int i;

	printf("  Machine:                           ");
	for (i = 0; i < sizeof(machines) / sizeof(machines[0]); i++)
	{
		if (machines[i].id == machine)
		{
			printf("%s\n", machines[i].name);
			return;
		}
	}
	printf("<unknown>: 0x%x\n", machine);
}

/**
 * print_common - prints the fields shared by ELF32 and ELF64
 * @ident: ELF identification
 * @type: ELF type
 * @machine: ELF machine
 * @version: ELF version
 */
static void print_common(unsigned char *ident, unsigned short type,
			 unsigned short machine, unsigned int version)
{
	printf("ELF Header:\n");
	print_magic(ident);
	print_class(ident[EI_CLASS]);
	print_data(ident[EI_DATA]);
	print_version(ident[EI_VERSION]);
	print_osabi(ident[EI_OSABI]);
	printf("  ABI Version:                       %u\n",
	       ident[EI_ABIVERSION]);
	print_type(type);
	print_machine(machine);
	printf("  Version:                           0x%x\n", version);
}

/**
 * print_header32 - prints an ELF32 header
 * @h: ELF32 header
 */
void print_header32(Elf32_Ehdr *h)
{
	print_common(h->e_ident, h->e_type, h->e_machine, h->e_version);
	printf("  Entry point address:               0x%x\n", h->e_entry);
	printf("  Start of program headers:          %u (bytes into file)\n",
	       h->e_phoff);
	printf("  Start of section headers:          %u (bytes into file)\n",
	       h->e_shoff);
	printf("  Flags:                             0x%x\n", h->e_flags);
	printf("  Size of this header:               %u (bytes)\n",
	       h->e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n",
	       h->e_phentsize);
	printf("  Number of program headers:         %u\n", h->e_phnum);
	printf("  Size of section headers:           %u (bytes)\n",
	       h->e_shentsize);
	printf("  Number of section headers:         %u\n", h->e_shnum);
	printf("  Section header string table index: %u\n", h->e_shstrndx);
}

/**
 * print_header64 - prints an ELF64 header
 * @h: ELF64 header
 */
void print_header64(Elf64_Ehdr *h)
{
	print_common(h->e_ident, h->e_type, h->e_machine, h->e_version);
	printf("  Entry point address:               0x%lx\n",
	       (unsigned long)h->e_entry);
	printf("  Start of program headers:          %lu (bytes into file)\n",
	       (unsigned long)h->e_phoff);
	printf("  Start of section headers:          %lu (bytes into file)\n",
	       (unsigned long)h->e_shoff);
	printf("  Flags:                             0x%x\n", h->e_flags);
	printf("  Size of this header:               %u (bytes)\n",
	       h->e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n",
	       h->e_phentsize);
	printf("  Number of program headers:         %u\n", h->e_phnum);
	printf("  Size of section headers:           %u (bytes)\n",
	       h->e_shentsize);
	printf("  Number of section headers:         %u\n", h->e_shnum);
	printf("  Section header string table index: %u\n", h->e_shstrndx);
}
