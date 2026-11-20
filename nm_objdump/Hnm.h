#ifndef HNM_H
#define HNM_H

#include <elf.h>
#include <stddef.h>
#include <stdint.h>

/**
 * struct elf_file_s - ELF file loaded in memory
 * @prog: name of the program (for error messages)
 * @name: name of the file
 * @data: raw contents of the file
 * @size: size of the file in bytes
 * @is64: 1 if the file is ELFCLASS64, 0 if ELFCLASS32
 * @big: 1 if the file is big endian, 0 if little endian
 */
typedef struct elf_file_s
{
	const char *prog;
	const char *name;
	const unsigned char *data;
	size_t size;
	int is64;
	int big;
} elf_file_t;

/**
 * struct sect_s - class independent section header
 * @name: offset of the name in the section header string table
 * @type: section type
 * @flags: section flags
 * @offset: offset of the section in the file
 * @size: size of the section
 * @link: link to another section
 * @entsize: size of an entry
 */
typedef struct sect_s
{
	uint32_t name;
	uint32_t type;
	uint64_t flags;
	uint64_t offset;
	uint64_t size;
	uint32_t link;
	uint64_t entsize;
} sect_t;

/**
 * struct sym_s - class independent symbol
 * @name: offset of the name in the string table
 * @info: type and binding
 * @shndx: index of the related section
 * @value: value of the symbol
 * @size: size of the symbol
 */
typedef struct sym_s
{
	uint32_t name;
	unsigned char info;
	uint16_t shndx;
	uint64_t value;
	uint64_t size;
} sym_t;

/* endian.c */
uint16_t rd16(const elf_file_t *ef, size_t off);
uint32_t rd32(const elf_file_t *ef, size_t off);
uint64_t rd64(const elf_file_t *ef, size_t off);
uint64_t rdaddr(const elf_file_t *ef, size_t off);

/* elf_parse.c */
int check_elf(elf_file_t *ef);
size_t sect_count(const elf_file_t *ef);
int get_section(const elf_file_t *ef, size_t idx, sect_t *s);
int get_symbol(const elf_file_t *ef, const sect_t *tab, size_t idx,
	       sym_t *sym);
const char *get_str(const elf_file_t *ef, const sect_t *tab, uint32_t off);

/* symbols.c */
int print_symbols(const elf_file_t *ef);

/* archive.c */
int is_archive(const unsigned char *data, size_t size);
int process_archive(const char *prog, const unsigned char *data,
		    size_t size);

/* hnm_main.c */
int process_elf(const char *prog, const char *name,
		const unsigned char *data, size_t size, int header);

/* sym_type.c */
char sym_type(const elf_file_t *ef, const sym_t *sym);

#endif
