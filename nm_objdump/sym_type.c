#include <ctype.h>
#include <string.h>
#include "hnm.h"

/**
 * coff_type - letter given by GNU nm to some well known section names
 * @name: section name
 *
 * Return: the letter, or '?' if the name is not a known one
 */
static char coff_type(const char *name)
{
	static const char * const names[] = {
		".bss", ".code", ".data", "*DEBUG*", ".debug", ".drectve",
		".edata", ".fini", ".idata", ".init", ".pdata", ".rdata",
		".rodata", ".sbss", ".scommon", ".sdata", ".text", ".vars",
		".zerovars", NULL};
	static const char types[] = "btdNNietitprrscgtdb";
	size_t len;
	int i;

	for (i = 0; names[i]; i++)
	{
		len = strlen(names[i]);
		if (!strncmp(name, names[i], len))
			return (types[i]);
	}
	return ('?');
}

/**
 * is_debug_name - check if a section name is a debugging section
 * @name: section name
 *
 * Return: 1 if it is a debugging section, 0 otherwise
 */
static int is_debug_name(const char *name)
{
	return (!strncmp(name, ".debug", 6) || !strncmp(name, ".zdebug", 7) ||
		!strncmp(name, ".gnu.debuglto_", 14) ||
		!strncmp(name, ".stab", 5) || !strncmp(name, ".line", 5) ||
		!strncmp(name, ".gnu.linkonce.wi.", 17));
}

/**
 * sect_type - letter for a symbol defined in a regular section
 * @ef: ELF file
 * @shndx: section index
 *
 * Return: letter describing the section (lowercase except 'N'), or '?'
 */
static char sect_type(const elf_file_t *ef, uint16_t shndx)
{
	sect_t s, shstr;
	uint32_t stridx = rd16(ef, ef->is64 ? 0x3E : 0x32);
	const char *name = "";
	char c;

	if (get_section(ef, shndx, &s) == -1)
		return ('?');
	if (stridx == SHN_XINDEX && get_section(ef, 0, &shstr) == 0)
		stridx = shstr.link;
	if (get_section(ef, stridx, &shstr) == 0)
		name = get_str(ef, &shstr, s.name);
	c = coff_type(name);
	if (c != '?')
		return (c);
	if (s.flags & SHF_EXECINSTR)
		return ('t');
	if ((s.flags & SHF_ALLOC) && s.type != SHT_NOBITS)
		return ((s.flags & SHF_WRITE) ? 'd' : 'r');
	if (s.type == SHT_NOBITS)
		return ('b');
	if (is_debug_name(name))
		return ('N');
	if (!(s.flags & SHF_WRITE))
		return ('n');
	return ('?');
}

/**
 * sym_type - compute the nm letter of a symbol
 * @ef: ELF file
 * @sym: the symbol
 *
 * Return: the letter
 */
char sym_type(const elf_file_t *ef, const sym_t *sym)
{
	unsigned char bind = ELF64_ST_BIND(sym->info);
	unsigned char type = ELF64_ST_TYPE(sym->info);
	char c;

	if (sym->shndx == SHN_COMMON)
		return ('C');
	if (sym->shndx == SHN_UNDEF)
	{
		if (bind == STB_WEAK)
			return (type == STT_OBJECT ? 'v' : 'w');
		return ('U');
	}
	if (type == STT_GNU_IFUNC)
		return ('i');
	if (bind == STB_WEAK)
		return (type == STT_OBJECT ? 'V' : 'W');
	if (bind == STB_GNU_UNIQUE)
		return ('u');
	if (bind != STB_LOCAL && bind != STB_GLOBAL)
		return ('?');
	if (sym->shndx != SHN_ABS && sym->shndx >= SHN_LORESERVE)
		return ('?');
	c = 'a';
	if (sym->shndx != SHN_ABS)
		c = sect_type(ef, sym->shndx);
	if (bind == STB_GLOBAL)
		c = toupper(c);
	return (c);
}
