#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/**
 * print_caught - Handler for SIGINT
 * @signum: The number of the signal that was caught
 */
static void print_caught(int signum)
{
	printf("Caught %d\n", signum);
}

/**
 * main - Waits for SIGINT without loop or sleep
 *
 * Return: EXIT_SUCCESS, or EXIT_FAILURE on error
 */
int main(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = print_caught;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (EXIT_FAILURE);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
