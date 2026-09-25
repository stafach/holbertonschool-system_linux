```makefile
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

0-hreadelf: 0-hreadelf.c elf_header.c
	$(CC) $(CFLAGS) -o 0-hreadelf 0-hreadelf.c elf_header.c

clean:
	rm -f 0-hreadelf

re: clean 0-hreadelf
