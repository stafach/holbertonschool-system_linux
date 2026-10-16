#include "signals.h"

/**
 * print_gotcha - Handler called each time SIGINT is caught
 * @signum: The number of the signal that was caught
 */
static void print_gotcha(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - Sets a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, print_gotcha) == SIG_ERR)
		return (-1);
	return (0);
}
