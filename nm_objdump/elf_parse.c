#include "hnm.h"

/**
 * check_elf - validate the ELF identification and header size
 * @ef: ELF file, is64 and big are filled on success
 *
 * Return: 0 on success, -1 if the file is not a supported ELF file
 */
int check_elf(elf_file_t *ef)
{
	const unsigned char *id = ef->data;

	if (ef->size < EI_NIDENT || id[EI_MAG0] != ELFMAG0 ||
	    id[EI_MAG1] != ELFMAG1 || id[EI_MAG2] != ELFMAG2 ||
	    id[EI_MAG3] != ELFMAG3)
		return (-1);
	if (id[EI_CLASS] != ELFCLASS32 && id[EI_CLASS] != ELFCLASS64)
		return (-1);
	if (id[EI_DATA] != ELFDATA2LSB && id[EI_DATA] != ELFDATA2MSB)
		return (-1);
	ef->is64 = id[EI_CLASS] == ELFCLASS64;
	ef->big = id[EI_DATA] == ELFDATA2MSB;
	if (ef->size < (ef->is64 ? sizeof(Elf64_Ehdr) : sizeof(Elf32_Ehdr)))
		return (-1);
	return (0);
}

/**
 * sect_count - number of section headers (handles extended numbering)
 * @ef: ELF file
 *
 * Return: number of sections, 0 if none or invalid
 */
size_t sect_count(const elf_file_t *ef)
{
	uint64_t shoff = rdaddr(ef, ef->is64 ? 0x28 : 0x20);
	size_t shentsize = rd16(ef, ef->is64 ? 0x3A : 0x2E);
	size_t num = rd16(ef, ef->is64 ? 0x3C : 0x30);
	size_t min = ef->is64 ? sizeof(Elf64_Shdr) : sizeof(Elf32_Shdr);

	if (shoff == 0 || shentsize < min || shoff >= ef->size)
		return (0);
	if (num == 0 && ef->size - shoff >= min)
		num = rdaddr(ef, shoff + (ef->is64 ? 32 : 20));
	if (num > (ef->size - shoff) / shentsize)
		return (0);
	return (num);
}

/**
 * get_section - read a section header
 * @ef: ELF file
 * @idx: index of the section
 * @s: where to store the section header
 *
 * Return: 0 on success, -1 on error
 */
int get_section(const elf_file_t *ef, size_t idx, sect_t *s)
{
	uint64_t shoff = rdaddr(ef, ef->is64 ? 0x28 : 0x20);
	size_t shentsize = rd16(ef, ef->is64 ? 0x3A : 0x2E);
	size_t off;

	if (idx >= sect_count(ef))
		return (-1);
	off = shoff + idx * shentsize;
	s->name = rd32(ef, off);
	s->type = rd32(ef, off + 4);
	s->flags = rdaddr(ef, off + 8);
	s->offset = rdaddr(ef, off + (ef->is64 ? 24 : 16));
	s->size = rdaddr(ef, off + (ef->is64 ? 32 : 20));
	s->link = rd32(ef, off + (ef->is64 ? 40 : 24));
	s->entsize = rdaddr(ef, off + (ef->is64 ? 56 : 36));
	return (0);
}

/**
 * get_symbol - read a symbol from a symbol table
 * @ef: ELF file
 * @tab: symbol table section
 * @idx: index of the symbol
 * @sym: where to store the symbol
 *
 * Return: 0 on success, -1 on error
 */
int get_symbol(const elf_file_t *ef, const sect_t *tab, size_t idx,
	       sym_t *sym)
{
	size_t esz = ef->is64 ? sizeof(Elf64_Sym) : sizeof(Elf32_Sym);
	uint64_t off = tab->offset + idx * esz;

	if (tab->offset > ef->size || off + esz > ef->size)
		return (-1);
	sym->name = rd32(ef, off);
	if (ef->is64)
	{
		sym->info = ef->data[off + 4];
		sym->shndx = rd16(ef, off + 6);
		sym->value = rd64(ef, off + 8);
		sym->size = rd64(ef, off + 16);
	}
	else
	{
		sym->value = rd32(ef, off + 4);
		sym->size = rd32(ef, off + 8);
		sym->info = ef->data[off + 12];
		sym->shndx = rd16(ef, off + 14);
	}
	return (0);
}

/**
 * get_str - get a string from a string table section
 * @ef: ELF file
 * @tab: string table section
 * @off: offset of the string in the table
 *
 * Return: pointer to the string, or "" if out of bounds / unterminated
 */
const char *get_str(const elf_file_t *ef, const sect_t *tab, uint32_t off)
{
	uint64_t i;

	if (tab->offset >= ef->size || off >= tab->size)
		return ("");
	for (i = tab->offset + off; i < ef->size &&
	     i < tab->offset + tab->size; i++)
		if (ef->data[i] == '\0')
			return ((const char *)ef->data + tab->offset + off);
	return ("");
}
