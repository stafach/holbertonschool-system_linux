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
 * handle_sigaction - Sets a handler for the signal SIGINT using sigaction
 *
 * Return: 0 on success, or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = print_gotcha;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (-1);
	return (0);
}
