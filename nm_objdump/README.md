# 0x03. C - ELF: nm

`hnm` reproduces the output of `GNU nm -p` (symbols listed in symbol table
order, without sorting).

## Build

```sh
make hnm
```

Compiled with `gcc -Wall -Werror -Wextra -pedantic`.

## Usage

```sh
./hnm [objfile ...]
```

With no argument, `a.out` is used. With several files, each listing is
preceded by a `\nfile:` header, like `nm`.

## Features

* 32-bit and 64-bit ELF files (`ELFCLASS32` / `ELFCLASS64`)
* Little and big endian files (all fields are read byte by byte, so the host
  endianness does not matter)
* All ELF types: relocatable objects, executables, shared objects, ...
* `ar` archives (`.a`): every member is listed under a `\nmember:` header
* Same symbol letters as GNU nm: `A B C D G N R T U V W ... u i v w ?`,
  lowercase for local symbols
* Same error messages: `No such file`, `is a directory`,
  `is not an ordinary file`, `file format not recognized`, `no symbols`

## Files

| File | Content |
| --- | --- |
| `hnm.h` | structures and prototypes |
| `hnm_main.c` | `main`, file reading, dispatch ELF / archive |
| `endian.c` | endian independent readers (16, 32, 64 bits) |
| `elf_parse.c` | ELF header check, section headers, symbols, strings |
| `symbols.c` | symbol table lookup and `nm -p` output |
| `sym_type.c` | computation of the symbol letter |
| `archive.c` | `ar` archive support (GNU and BSD long names) |
| `Makefile` | rules `hnm`, `all`, `clean`, `fclean`, `re` |