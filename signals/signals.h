#ifndef SIGNALS_H
#define SIGNALS_H

#include <stdio.h>
#include <signal.h>
#include <string.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);

#endif
