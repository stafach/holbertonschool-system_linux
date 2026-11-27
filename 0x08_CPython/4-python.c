#include <Python.h>
#include <stdio.h>

/**
 * put_utf8 - prints a code point encoded in UTF-8
 * @c: the code point
 */
static void put_utf8(Py_UCS4 c)
{
	if (c < 0x80)
	{
		putchar(c);
	}
	else if (c < 0x800)
	{
		putchar(0xC0 | (c >> 6));
		putchar(0x80 | (c & 0x3F));
	}
	else if (c < 0x10000)
	{
		putchar(0xE0 | (c >> 12));
		putchar(0x80 | ((c >> 6) & 0x3F));
		putchar(0x80 | (c & 0x3F));
	}
	else
	{
		putchar(0xF0 | (c >> 18));
		putchar(0x80 | ((c >> 12) & 0x3F));
		putchar(0x80 | ((c >> 6) & 0x3F));
		putchar(0x80 | (c & 0x3F));
	}
}

/**
 * print_python_string - prints basic info about a Python string
 * @p: pointer to a Python string object
 */
void print_python_string(PyObject *p)
{
	Py_ssize_t len, i;
	int kind;
	void *data;

	setbuf(stdout, NULL);
	printf("[.] string object info\n");
	if (!PyUnicode_Check(p))
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	len = PyUnicode_GET_LENGTH(p);
	kind = PyUnicode_KIND(p);
	data = PyUnicode_DATA(p);
	if (PyUnicode_IS_COMPACT_ASCII(p))
		printf("  type: compact ascii\n");
	else
		printf("  type: compact unicode object\n");
	printf("  length: %ld\n", (long)len);
	printf("  value: ");
	for (i = 0; i < len; i++)
		put_utf8(PyUnicode_READ(kind, data, i));
	printf("\n");
}
