CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
HNM_SRC = hnm_main.c endian.c elf_parse.c symbols.c sym_type.c archive.c
HNM_OBJ = $(HNM_SRC:.c=.o)

.PHONY: all clean fclean re

all: hnm

hnm: $(HNM_OBJ)
	$(CC) $(CFLAGS) $(HNM_OBJ) -o hnm

%.o: %.c hnm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(HNM_OBJ)

fclean: clean
	$(RM) hnm

re: fclean all
