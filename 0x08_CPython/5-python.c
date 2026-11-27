#include <Python.h>
#include <stdio.h>
#include <limits.h>

/**
 * print_python_int - prints a Python int as a C unsigned long int
 * @p: pointer to a Python int object
 */
void print_python_int(PyObject *p)
{
	Py_ssize_t size, ndigits, i;
	unsigned long int n = 0;
	digit *digits;

	setbuf(stdout, NULL);
	if (!PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	size = ((PyVarObject *)p)->ob_size;
	ndigits = size < 0 ? -size : size;
	digits = ((PyLongObject *)p)->ob_digit;
	for (i = ndigits - 1; i >= 0; i--)
	{
		if (n > (ULONG_MAX >> PyLong_SHIFT))
		{
			printf("C unsigned long int overflow\n");
			return;
		}
		n = (n << PyLong_SHIFT) + digits[i];
	}
	if (size < 0)
		printf("-");
	printf("%lu\n", n);
}
