#pragma once

#include <errno.h>

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#include "../../../TLibLibraryC/tlib.h"
#include "../../../TLinuxLibraryC/tlinux.h"

typedef struct
{
	TString* parameters;
	TBool waiting_flag;
} MenuParameters;

T_IMPORT_MENU_DECLARATION(MenuParameters)

void menu_remove(MenuParameters* const parameters);
void menu_set(MenuParameters* const parameters);
void menu_fork(MenuParameters* const parameters);
void menu_execve(MenuParameters* const parameters);
void menu_switch_flag(MenuParameters* const parameters);
