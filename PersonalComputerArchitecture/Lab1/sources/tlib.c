#include "tlib.h"

#include "../../../TLibLibraryC/tlib.c"

void T_CONTAINER(TMenu, void, menu_bar)(void* const parameters)
{
	if (parameters != nullptr) return;
	T_CLASS(TConsole, print)(kOutput, "Available COM-ports:\n");
	system("ls /dev/tnt*");  // NOLINT(concurrency-mt-unsafe)
	T_CLASS(TConsole, print)(kOutput, "\n");
}

T_IMPORT_MENU_DEFINITION(void)
