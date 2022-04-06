#include "tsyscalls.h"
#include "tconsole.h"

#include <stdlib.h>

void T_FUNCTION(syscall, pause)(void)
{
	T_CLASS(TConsole, print)(kOutput, "Press enter to continue...");
	T_CLASS(TConsole, echo)(false);
	T_CLASS(TConsole, clear)();
	T_CLASS(TConsole, echo)(true);
	T_CLASS(TConsole, print)(kOutput, "\n");
}
void T_FUNCTION(syscall, clear)(void)
{
#ifdef _WIN32
	system("cls");
#endif
#ifdef __linux__
	system("clear");
#endif
}
void T_FUNCTION(syscall, update)(void)
{
	T_FUNCTION(syscall, pause)();
	T_FUNCTION(syscall, clear)();
}
int register_at_exit(void(*parameter)(void))
{
	return atexit(parameter);
}
