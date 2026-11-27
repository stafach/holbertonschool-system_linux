#include <Python.h>
#include <stdio.h>

/**
 * print_python_list - prints basic info about a Python list
 * @p: pointer to a Python list object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t size, i;
	PyListObject *list = (PyListObject *)p;
	PyObject *item;

	size = Py_SIZE(p);
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", (long)size);
	printf("[*] Allocated = %ld\n", (long)list->allocated);
	for (i = 0; i < size; i++)
	{
		item = list->ob_item[i];
		printf("Element %ld: %s\n", (long)i, Py_TYPE(item)->tp_name);
	}
}
