#include "signals.h"

/**
 * print_sender - Handler for SIGQUIT, prints the PID of the sender
 * @signum: The number of the signal (unused)
 * @info: Information about the signal, including the sender's PID
 * @context: Unused
 */
static void print_sender(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	printf("SIGQUIT sent by %d\n", info->si_pid);
	fflush(stdout);
}

/**
 * trace_signal_sender - Sets a handler for SIGQUIT that prints the sender
 *
 * Return: 0 on success, or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = print_sender;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (-1);
	return (0);
}
