#include "tlib.h"

int main(const int argc, TMessage argv[])
{
	T_CLASS(TConsole, default_constructor)();

	T_CLASS(TConsole, print)(kOutput, "Parent process has started.\n");
	if (argc > 1) T_CLASS(TConsole, print)(kOutput, "Parent process has detected parameters:\n");
	for (int i = 1; argv[i] != nullptr; ++i)
	{
		T_CLASS(TConsole, print)(kOutput, "Parameter %d:\t%s\n", i, argv[i]);
	}

	TMessage options[] = { "Set parameters", "Fork", "Execve", "Switch the waiting flag", nullptr };
	const T_CONTAINER(TMenu, MenuParameters, Action) actions[] = { &menu_set, &menu_fork, &menu_execve, &menu_switch_flag };
	MenuParameters parameters = { nullptr, true };

	T_CONTAINER(TMenu, MenuParameters, menu)(options, actions, &parameters);
	menu_remove(&parameters);
}
