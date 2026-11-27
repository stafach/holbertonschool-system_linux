#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - prints basic info about a Python list
 * @p: pointer to a Python list object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;
	PyListObject *list = (PyListObject *)p;
	PyObject *item;

	setbuf(stdout, NULL);
	printf("[*] Python list info\n");
	if (!PyList_Check(p))
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	size = ((PyVarObject *)p)->ob_size;
	printf("[*] Size of the Python List = %ld\n", (long)size);
	printf("[*] Allocated = %ld\n", (long)list->allocated);
	for (i = 0; i < size; i++)
	{
		item = list->ob_item[i];
		printf("Element %ld: %s\n", (long)i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
		else if (PyFloat_Check(item))
			print_python_float(item);
	}
}

/**
 * print_python_bytes - prints basic info about a Python bytes object
 * @p: pointer to a Python bytes object
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i, max;
	char *str;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = ((PyVarObject *)p)->ob_size;
	str = ((PyBytesObject *)p)->ob_sval;
	printf("  size: %ld\n", (long)size);
	printf("  trying string: %s\n", str);
	max = size + 1 > 10 ? 10 : size + 1;
	printf("  first %ld bytes:", (long)max);
	for (i = 0; i < max; i++)
		printf(" %02x", (unsigned char)str[i]);
	printf("\n");
}

/**
 * float_repr - formats a double like Python's repr()
 * @d: the value
 * @buf: output buffer (at least 64 bytes)
 */
static void float_repr(double d, char *buf)
{
	int prec, exp;
	char tmp[64];

	if (isnan(d) || isinf(d))
	{
		sprintf(buf, "%s", isnan(d) ? "nan" : (d < 0 ? "-inf" : "inf"));
		return;
	}
	for (prec = 1; prec < 17; prec++)
	{
		sprintf(tmp, "%.*e", prec - 1, d);
		if (strtod(tmp, NULL) == d)
			break;
	}
	sprintf(tmp, "%.*e", prec - 1, d);
	exp = atoi(strchr(tmp, 'e') + 1);
	if (d == 0.0)
		exp = 0;
	if (exp < -4 || exp >= 16)
	{
		sprintf(buf, "%s", tmp);
		return;
	}
	if (prec - 1 - exp > 0)
		sprintf(buf, "%.*f", prec - 1 - exp, d);
	else
		sprintf(buf, "%.0f.0", d);
}

/**
 * print_python_float - prints basic info about a Python float object
 * @p: pointer to a Python float object
 */
void print_python_float(PyObject *p)
{
	char buf[64];

	setbuf(stdout, NULL);
	printf("[.] float object info\n");
	if (!PyFloat_Check(p))
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	float_repr(((PyFloatObject *)p)->ob_fval, buf);
	printf("  value: %s\n", buf);
}
