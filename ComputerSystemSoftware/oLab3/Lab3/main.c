// ReSharper disable CppParameterMayBeConstPtrOrRef
// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppClangTidyMiscMisplacedConst
#include "lab3.h"

const TAnsiColor kParentColor = kGreen;
const TAnsiColor kChildColor = kYellow;
const TAnsiColor kExtraColor = kCyan;

typedef struct
{
	TString* parameters;
	TFlag waiting_flag;
} MenuParameters;
#define MENU_PARAMETERS MenuParameters
#include "../../../Tlib Library C/Tlib Library C/timport/tui.h"

void menu_show(MenuParameters* const parameters)
{
	if (parameters->parameters == nullptr)
	{
		T_CLASS(TConsole, print)(kOutput, "Parameters for children:No parameters.\n");
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

/*
typedef void (*MenuAction)(MenuParameters*);
void T_CONTAINER(TMenu, MenuParameters, menu_bar)(MenuParameters* const parameters)
{
	T_CLASS(TConsole, print)(kLog, "Parent process pid:\t%d\n", getppid());
	T_CLASS(TConsole, print)(kLog, "Current process pid:\t%d\n", getpid());
	T_CLASS(TConsole, print)(kLog, "Waiting flag:\t\t%s\n", parameters->waiting_flag == true ? "true" : "false");
	menu_show(parameters);
}
void menu(TMessage* const options, const MenuAction* const actions, MenuParameters* const parameters)
{
	while (true)
	{
		T_CLASS(TConsole, print)(kOutput, "\tParent process data:\n");
		T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
		T_CLASS(TConsole, print)(kOutput, "Menu options:\n");
		size_t size = 0u;
		while (options[size] != nullptr)
		{
			T_CLASS(TConsole, print)(kOutput, "\t%zu)\t%s;\n", size + 1, options[size]);
			++size;
		}
		T_CLASS(TConsole, print)(kOutput, "\t%zu)\t%s.\n", size + 1, "Quit");
		++size;

		size_t option;
		do
		{
			TString const string = T_CLASS(TConsole, getline)("option number", false);  // NOLINT(misc-misplaced-const)
			option = T_CLASS(TMessage, to_size_t)(string);
			T_CLASS(TString, clear)(string);
		}
		while (option == 0u || option > size);
		if (option == size) return;
		actions[--option](parameters);
		
		syscall__update();
	}
}
*/

#define TEMPLATE_TYPE TString
#include "../../../Tlib Library C/Tlib Library C/timport/tmemory.h"

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
	const size_t size = T_CONVERTER(TMessage, size_t)(string);
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
	if (pid == -1)
	{
		T_CLASS(TConsole, print)(kError, "Error occurred, error code - %d\n", errno); exit(errno);
	}
	if (pid == 0)
	{
		T_CLASS(TConsole, print)(kLog, "Child process has started...\n");
		T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
		T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
		T_CLASS(TConsole, print)(kLog, "Child process called menu_remove(parameters) function...\n");
		menu_remove(parameters);
		exit(123);  // NOLINT(concurrency-mt-unsafe)
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
		if (pid == -1)
		{
			T_CLASS(TConsole, print)(kError, "Error occurred, error code - %d\n", errno); exit(errno);
		}
		if (pid == 0)
		{
			 
			T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
			T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
			 
			const TString args[] = { "gcc/dirwalk", "gcc", "-fs", nullptr };
			 
			T_CLASS(TConsole, print)(kLog, "Child process created. Please, wait for execution start...\n");
			 
			execve("gcc/dirwalk", args, nullptr);
			exit(0);
		}
		wait(&child_status);
		T_CLASS(TConsole, print)(kOutput, "Child process has ended with %d exit status\n", child_status);
	}
	 
	TString const process_name = T_CLASS(TConsole, getline)("path to the process", false);
	{
		const pid_t pid = fork();
		if (pid == -1)
		{
			T_CLASS(TConsole, print)(kError, "Error occurred, error code - %d\n", errno); exit(errno);
		}
		if (pid == 0)
		{
			 
			T_CLASS(TConsole, print)(kLog, "\tChild process data:\n");
			T_CONTAINER(TMenu, MenuParameters, menu_bar)(parameters);
			 
			T_CLASS(TConsole, print)(kLog, "Child process created. Please, wait for execution start...\n");
			if (execve(process_name, parameters->parameters, nullptr) == -1)
			{
				 
				T_CLASS(TConsole, print)(kError, "Error occurred, error code - %d\n", errno); exit(errno);
			}
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

void at_exit(void)
{
	T_CLASS(TConsole, end)();
}

int main(const int argc, TMessage argv[])
{
	T_CLASS(TConsole, start)(nullptr, nullptr, nullptr, nullptr);
	T_CLASS(TConsole, set_format)(kInput, kNormal, true, kYellow);
	T_CLASS(TConsole, set_format)(kOutput, kNormal, true, kGreen);
	T_CLASS(TConsole, set_format)(kError, kNormal, false, kRed);
	T_CLASS(TConsole, set_format)(kLog, kNormal, true, kCyan);
	register_at_exit(at_exit);

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

	T_CLASS(TConsole, print)(kOutput, "Parent process has ended.\n");
}
