CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = 0-hreadelf.c elf_header.c elf_header2.c endian.c

0-hreadelf: $(SRC) elf_header.h
	$(CC) $(CFLAGS) -o 0-hreadelf $(SRC)

clean:
	rm -f 0-hreadelf

re: clean 0-hreadelf

.PHONY: clean re
