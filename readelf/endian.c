#include <elf.h>
#include "elf_header.h"

/**
 * swap16 - reverses the bytes of a 16-bit value
 * @v: value
 *
 * Return: swapped value
 */
unsigned short swap16(unsigned short v)
{
	return ((unsigned short)((v >> 8) | (v << 8)));
}

/**
 * swap32 - reverses the bytes of a 32-bit value
 * @v: value
 *
 * Return: swapped value
 */
unsigned int swap32(unsigned int v)
{
	return (((v >> 24) & 0xff) | ((v >> 8) & 0xff00) |
		((v << 8) & 0xff0000) | ((v << 24) & 0xff000000));
}

/**
 * swap64 - reverses the bytes of a 64-bit value
 * @v: value
 *
 * Return: swapped value
 */
unsigned long swap64(unsigned long v)
{
	return (((unsigned long)swap32(v & 0xffffffff) << 32) |
		swap32(v >> 32));
}

/**
 * swap_header32 - converts a big endian ELF32 header to host order
 * @h: ELF32 header
 */
void swap_header32(Elf32_Ehdr *h)
{
	h->e_type = swap16(h->e_type);
	h->e_machine = swap16(h->e_machine);
	h->e_version = swap32(h->e_version);
	h->e_entry = swap32(h->e_entry);
	h->e_phoff = swap32(h->e_phoff);
	h->e_shoff = swap32(h->e_shoff);
	h->e_flags = swap32(h->e_flags);
	h->e_ehsize = swap16(h->e_ehsize);
	h->e_phentsize = swap16(h->e_phentsize);
	h->e_phnum = swap16(h->e_phnum);
	h->e_shentsize = swap16(h->e_shentsize);
	h->e_shnum = swap16(h->e_shnum);
	h->e_shstrndx = swap16(h->e_shstrndx);
}

/**
 * swap_header64 - converts a big endian ELF64 header to host order
 * @h: ELF64 header
 */
void swap_header64(Elf64_Ehdr *h)
{
	h->e_type = swap16(h->e_type);
	h->e_machine = swap16(h->e_machine);
	h->e_version = swap32(h->e_version);
	h->e_entry = swap64(h->e_entry);
	h->e_phoff = swap64(h->e_phoff);
	h->e_shoff = swap64(h->e_shoff);
	h->e_flags = swap32(h->e_flags);
	h->e_ehsize = swap16(h->e_ehsize);
	h->e_phentsize = swap16(h->e_phentsize);
	h->e_phnum = swap16(h->e_phnum);
	h->e_shentsize = swap16(h->e_shentsize);
	h->e_shnum = swap16(h->e_shnum);
	h->e_shstrndx = swap16(h->e_shstrndx);
}
