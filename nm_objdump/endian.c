#include "Hnm.h"

/**
 * rd16 - read a 16 bit value respecting the file endianness
 * @ef: ELF file
 * @off: offset in the file
 *
 * Return: the value
 */
uint16_t rd16(const elf_file_t *ef, size_t off)
{
	const unsigned char *p = ef->data + off;

	if (ef->big)
		return ((uint16_t)p[0] << 8 | p[1]);
	return ((uint16_t)p[1] << 8 | p[0]);
}

/**
 * rd32 - read a 32 bit value respecting the file endianness
 * @ef: ELF file
 * @off: offset in the file
 *
 * Return: the value
 */
uint32_t rd32(const elf_file_t *ef, size_t off)
{
	const unsigned char *p = ef->data + off;
	uint32_t v = 0;
	int i;

	for (i = 0; i < 4; i++)
	{
		if (ef->big)
			v = (v << 8) | p[i];
		else
			v = (v << 8) | p[3 - i];
	}
	return (v);
}

/**
 * rd64 - read a 64 bit value respecting the file endianness
 * @ef: ELF file
 * @off: offset in the file
 *
 * Return: the value
 */
uint64_t rd64(const elf_file_t *ef, size_t off)
{
	const unsigned char *p = ef->data + off;
	uint64_t v = 0;
	int i;

	for (i = 0; i < 8; i++)
	{
		if (ef->big)
			v = (v << 8) | p[i];
		else
			v = (v << 8) | p[7 - i];
	}
	return (v);
}

/**
 * rdaddr - read an address / offset sized value (32 or 64 bit)
 * @ef: ELF file
 * @off: offset in the file
 *
 * Return: the value
 */
uint64_t rdaddr(const elf_file_t *ef, size_t off)
{
	if (ef->is64)
		return (rd64(ef, off));
	return (rd32(ef, off));
}
