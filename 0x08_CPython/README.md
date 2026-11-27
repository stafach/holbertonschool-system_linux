# Python - CPython

Exploring the internals of CPython 3.9: Big O of list operations and C
functions that print information about Python objects (`list`, `bytes`,
`float`, `str`, `int`) by reading their C structures directly.

## Requirements

* Ubuntu 20.04 LTS, Python 3.9, `gcc 9.4.0`
* Compiled with `-Wall -Werror -Wextra -pedantic -std=c99`
* Code follows the `Betty` style

## Compilation

Each C file is compiled as a shared library, for example:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,libPython.so \
    -o libPython.so -fPIC -I/usr/include/python3.9 2-python.c
```

and used from Python with `ctypes`:

```python
import ctypes
lib = ctypes.CDLL('./libPython.so')
lib.print_python_list.argtypes = [ctypes.py_object]
lib.print_python_list([1, b'Hello', 3.14])
```

## Tasks

| # | File | Description |
| --- | --- | --- |
| 0 | `0-lists` | Big O notation of 12 list operations (assign, append, concatenate, insert, remove, pop, clear, count, sort, reverse, delete) |
| 1 | `1-python.c` | `print_python_list`: size, allocated space and type of each element of a list (library `libPyList.so`) |
| 2 | `2-python.c` | `print_python_list` and `print_python_bytes`: size, string and first bytes (max 10) of a `bytes` object, without `Py_SIZE`, `Py_TYPE`, ... |
| 3 | `3-python.c` | `print_python_list`, `print_python_bytes` and `print_python_float`, with error messages for invalid objects and unbuffered output |
| 4 | `4-python.c` | `print_python_string`: type (`compact ascii` / `compact unicode object`), length and value of a `str` |
| 5 | `5-python.c` | `print_python_int`: converts a Python `int` to an `unsigned long int` using only `PyLong_SHIFT` and `PyLong_Check`, prints `C unsigned long int overflow` if too big |

## Author

Holberton School student
