#include "signals.h"

/**
 * main - Prints a description of a given signal
 * @argc: Number of arguments
 * @argv: Arguments, argv[1] is the signal number
 *
 * Return: EXIT_SUCCESS, or EXIT_FAILURE on wrong usage
 */
int main(int argc, char **argv)
{
	int signum;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	signum = atoi(argv[1]);
	printf("%d: %s\n", signum, strsignal(signum));
	return (EXIT_SUCCESS);
}
