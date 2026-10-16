#include "signals.h"

/**
 * main - Sends the signal SIGINT to a process, given its PID
 * @argc: Number of arguments
 * @argv: Arguments, argv[1] is the PID of the target process
 *
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	pid_t pid;

	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	pid = atoi(argv[1]);
	if (kill(pid, SIGINT) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
