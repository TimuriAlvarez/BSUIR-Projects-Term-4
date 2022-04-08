#include "tlib.h"

#define T_CHECK_FORK(T_PID) { if (T_PID == -1) T_THROW_EXCEPTION("Lab", "Failed to fork process", E_LOCATION, true, 0xCE01F0, ); }
#define T_THROW_EXECVE_EXCEPTION(T_PROC_NAME) T_THROW_EXCEPTION(T_PROC_NAME, "Failed to execute process", E_LOCATION, true, 0xCE01FE, )

void menu_show(MenuParameters* const parameters)
{
	if (parameters->parameters == nullptr)
	{
		T_CLASS(TConsole, print)(kOutput, "Parameters for children: No parameters.\n");
		return;
	}
	T_CLASS(TConsole, print)(kOutput, "Parameters for children:\n");
	for (size_t i = 0u; parameters->parameters[i] != nullptr; ++i)
	{
		T_CLASS(TConsole, print)(kOutput, "\tParameter %zu:\t%s\n", i + 1, parameters->parameters[i]);
	}
}
void T_CONTAINER(TMenu, MenuParameters, menu_bar)(MenuParameters* const parameters)
{
	T_CLASS(TConsole, print)(kLog, "Parent process pid:\t%d\n", getppid());
	T_CLASS(TConsole, print)(kLog, "Current process pid:\t%d\n", getpid());
	T_CLASS(TConsole, print)(kLog, "Waiting flag:\t\t%s\n", parameters->waiting_flag == true ? "true" : "false");
	menu_show(parameters);
}
T_IMPORT_MENU_DEFINITION(MenuParameters)

T_IMPORT_MEMORY_DECLARATION(TString)

void menu_remove(MenuParameters* const parameters)
{
	T_CLASS(TConsole, print)(kLog, "Removing parameters...\n");
	if (parameters->parameters != nullptr)
		for (size_t i = 0u; parameters->parameters[i] != nullptr; ++i)
			T_CLASS(TString, clear)(parameters->parameters[i]);
	T_FUNCTION(delete, TString)(parameters->parameters);
}
void menu_set(MenuParameters* const parameters)
{
	if (T_CLASS(TConsole, confirmation)("reset parameters") == false) return;
	menu_remove(parameters);
	T_CLASS(TConsole, print)(kOutput, "Enter the new ones...\n");
	TString const string = T_CLASS(TConsole, getline)("number of parameters", false);  // NOLINT(misc-misplaced-const)
	const size_t size = T_CONVERTER(TString, size_t)(string);
	parameters->parameters = T_FUNCTION(new, TString)(size + 1u);
	for (size_t i = 0u; i < size; ++i)
	{
		T_CLASS(TConsole, print)(kOutput, "Enter parameter %zu: ", i + 1u);
		parameters->parameters[i] = T_CLASS(TConsole, getline)(nullptr, false);
	}

	T_CLASS(TString, clear)(string);
}
void menu_fork(MenuParameters* const parameters)
{
	syscall__clear();
	T_CLASS(TConsole, print)(kOutput, "\tParent process data:\n");
	T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
	int child_status;
	const pid_t pid = fork();
	T_CHECK_FORK(pid)
	if (pid == 0)
	{
		T_CLASS(TConsole, print)(kLog, "Child process has started...\n");
		T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
		T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
		T_CLASS(TConsole, print)(kLog, "Child process called menu_remove(parameters) function...\n");
		menu_remove(parameters);
		exit(123);
	}
	if (parameters->waiting_flag)
	{
		wait(&child_status);
		T_CLASS(TConsole, print)(kOutput, "Child process has ended with %d exit status\n", child_status);
	}
	T_CLASS(TConsole, print)(kOutput, "Parent process is running...\n");
}
void menu_execve(MenuParameters* const parameters)
{
	syscall__clear();
	T_CLASS(TConsole, print)(kOutput, "\tParent process data:\n");
	T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
	int child_status;
	{
		const pid_t pid = fork();
		T_CHECK_FORK(pid)
		if (pid == 0)
		{

			T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
			T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);

			const TString args[] = { "bin/dirwalk", "bin", "-fls", nullptr };

			T_CLASS(TConsole, print)(kLog, "Child process created. Please, wait for execution start...\n");

			execve("bin/dirwalk", args, nullptr);
			exit(0);
		}
		wait(&child_status);
		T_CLASS(TConsole, print)(kOutput, "Child process has ended with %d exit status\n", child_status);
	}

	TString const process_name = T_CLASS(TConsole, getline)("path to the process", false);
	{
		const pid_t pid = fork();
		T_CHECK_FORK(pid)
		if (pid == 0)
		{

			T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
			T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);

			T_CLASS(TConsole, print)(kLog, "Child process created. Please, wait for execution start...\n");
			if (execve(process_name, parameters->parameters, nullptr) == -1) T_THROW_EXECVE_EXCEPTION(process_name);
		}
		if (parameters->waiting_flag)
		{
			wait(&child_status);

			T_CLASS(TConsole, print)(kOutput, "Child process has ended with %d exit status\n", child_status);
		}
	}
}
void menu_switch_flag(MenuParameters* const parameters)
{
	if (T_CLASS(TConsole, confirmation)("switch the waiting flag") == false) return;
	parameters->waiting_flag = !parameters->waiting_flag;
	T_CLASS(TConsole, print)(kOutput, "The flag was switched.\n");
}
