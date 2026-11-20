#include <stdio.h>
#include "Hnm.h"

/**
 * find_symtab - find the SHT_SYMTAB section and its string table
 * @ef: ELF file
 * @symtab: where to store the symbol table header
 * @strtab: where to store the string table header
 *
 * Return: number of symbols (including the null one), 0 if none
 */
static size_t find_symtab(const elf_file_t *ef, sect_t *symtab,
			  sect_t *strtab)
{
	size_t i, n = sect_count(ef);
	size_t esz = ef->is64 ? sizeof(Elf64_Sym) : sizeof(Elf32_Sym);

	for (i = 0; i < n; i++)
	{
		if (get_section(ef, i, symtab) == -1)
			return (0);
		if (symtab->type != SHT_SYMTAB)
			continue;
		if (get_section(ef, symtab->link, strtab) == -1)
			return (0);
		return (symtab->size / esz);
	}
	return (0);
}

/**
 * print_one - print one symbol line in nm -p format
 * @ef: ELF file
 * @sym: the symbol
 * @name: the symbol name
 */
static void print_one(const elf_file_t *ef, const sym_t *sym,
		      const char *name)
{
	char c = sym_type(ef, sym);
	int width = ef->is64 ? 16 : 8;

	if (c == 'U' || c == 'w' || c == 'v')
		printf("%*s %c %s\n", width, "", c, name);
	else if (sym->shndx == SHN_COMMON)
		printf("%0*lx %c %s\n", width, (unsigned long)sym->size,
		       c, name);
	else
		printf("%0*lx %c %s\n", width, (unsigned long)sym->value,
		       c, name);
}

/**
 * print_symbols - print the symbol table of an ELF file like nm -p
 * @ef: ELF file
 *
 * Return: 0 on success, 1 if the file has no symbols
 */
int print_symbols(const elf_file_t *ef)
{
	sect_t symtab, strtab;
	sym_t sym;
	size_t i, n = find_symtab(ef, &symtab, &strtab);
	unsigned char type;

	if (n <= 1)
	{
		fflush(stdout);
		fprintf(stderr, "%s: %s: no symbols\n", ef->prog, ef->name);
		return (0);
	}
	for (i = 1; i < n; i++)
	{
		if (get_symbol(ef, &symtab, i, &sym) == -1)
			break;
		type = ELF64_ST_TYPE(sym.info);
		if (type == STT_SECTION || type == STT_FILE)
			continue;
		print_one(ef, &sym, get_str(ef, &strtab, sym.name));
	}
	return (0);
}
