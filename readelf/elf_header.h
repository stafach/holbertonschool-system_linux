#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include <elf.h>

void print_magic(unsigned char *ident);
void print_class(unsigned char class);
void print_data(unsigned char data);
void print_version(unsigned char version);
void print_osabi(unsigned char osabi);
void print_type(unsigned short type);
void print_machine(unsigned short machine);
void print_header(Elf64_Ehdr *header);

#endif
