#include <Python.h>
#include <stdio.h>

void print_python_bytes(PyObject *p);

/**
 * print_python_list - prints basic info about a Python list
 * @p: pointer to a Python list object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;
	PyListObject *list = (PyListObject *)p;
	PyObject *item;

	size = ((PyVarObject *)p)->ob_size;
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", (long)size);
	printf("[*] Allocated = %ld\n", (long)list->allocated);
	for (i = 0; i < size; i++)
	{
		item = list->ob_item[i];
		printf("Element %ld: %s\n", (long)i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
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
