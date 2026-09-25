#ifndef ELF_HEADER_H
#define ELF_HEADER_H

#include <elf.h>

void print_header32(Elf32_Ehdr *header);
void print_header64(Elf64_Ehdr *header);

#endif