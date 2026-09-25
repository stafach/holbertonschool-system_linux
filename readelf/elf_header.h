#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include <elf.h>

/* elf_header.c */
void print_magic(unsigned char *ident);
void print_class(unsigned char class);
void print_data(unsigned char data);
void print_version(unsigned char version);
void print_osabi(unsigned char osabi);

/* elf_header2.c */
void print_type(unsigned short type);
void print_machine(unsigned short machine);
void print_header32(Elf32_Ehdr *header);
void print_header64(Elf64_Ehdr *header);

/* endian.c */
unsigned short swap16(unsigned short v);
unsigned int swap32(unsigned int v);
unsigned long swap64(unsigned long v);
void swap_header32(Elf32_Ehdr *h);
void swap_header64(Elf64_Ehdr *h);

#endif
