#include <sys/types.h>

/**
 * pid_exist - Tests if a process exists, given its PID
 * @pid: The PID of the process to test
 *
 * Return: 1 if the process exists, or 0 otherwise
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0);
}
