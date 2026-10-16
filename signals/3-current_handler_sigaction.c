#include "signals.h"

/**
 * current_handler_sigaction - Retrieves the current handler of SIGINT using sigaction
 *
 * Return: A pointer to the current handler of SIGINT, or NULL on failure
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction act;
	if (sigaction(SIGINT, NULL, &act) == -1)
		return (NULL);
	return (act.sa_handler);
}
