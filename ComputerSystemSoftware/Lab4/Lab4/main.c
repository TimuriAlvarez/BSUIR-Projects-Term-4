// ReSharper disable CppClangTidyMiscMisplacedConst
#include "Lab4.h"
#include "parent.h"
#include "child.h"
#include <errno.h>

#define DELAY 30

int main(void)
{
	syscall__clear();
	console_start();
	register_at_exit(console_end);
	TVector__pid_t__Container const container = TVector__pid_t__constructor();

	while (true)
	{
		static TString string = nullptr;
		top_bar(container);

		T_CLASS(TString, clear)(string);
		T_CLASS(TConsole, print)(kOutput, "> ");
		string = T_CLASS(TConsole, getline)(nullptr, true);

		if (T_CLASS(TMessage, empty)(string))
		{
			syscall__clear();
			continue;
		}
		if (T_CLASS(TMessage, equal)(string, "q"))
		{
			T_CLASS(TConsole, print)(kOutput, "Quitting...\n");
			kill_all(container);
			TVector__pid_t__destructor(container);
			T_CLASS(TString, clear)(string);
			return 0;
		}
		if (T_CLASS(TMessage, equal)(string, "+"))
		{
			T_CLASS(TConsole, print)(kOutput, "Adding a child...\n");
			const pid_t pid = fork();
			if (pid == -1)
			{
				T_CLASS(TConsole, print)(kError, "Error occurred, error code - %d\n", errno);
				TException const exception = { nullptr, E_LOCATION, errno, errno, true };
				t_exception(exception);
			}
			if (pid == 0) child_function();
			TVector__pid_t__append(container, pid, true);
			T_CLASS(TConsole, print)(kOutput, "Child process %i was created\n", pid);
		}
		else if (T_CLASS(TMessage, equal)(string, "-"))
		{
			T_CLASS(TConsole, print)(kOutput, "Killing the last added child...\n");
			kill_last(container, true);
		}
		else if (T_CLASS(TMessage, equal)(string, "k"))
		{
			T_CLASS(TConsole, print)(kOutput, "Killing all children processes...\n");
			kill_all(container);
		}
		else if (T_CLASS(TMessage, equal)(string, "m"))
		{
			T_CLASS(TConsole, print)(kOutput, "Muting all children processes...\n");
			FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container) kill(*iterator, SIGUSR1);
			T_CLASS(TConsole, print)(kOutput, "All children processes are muted.\n");
		}
		else if (T_CLASS(TMessage, equal)(string, "u"))
		{
			T_CLASS(TConsole, print)(kOutput, "Unmuting all children processes...\n");
			FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container) kill(*iterator, SIGUSR2);
			T_CLASS(TConsole, print)(kOutput, "All children processes are unmuted.\n");
		}
		else if (T_CLASS(TMessage, equal)(string, "p"))
		{
			T_CLASS(TConsole, print)(kOutput, "Printing stats for all children process...\n");
			FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
			{
				kill(*iterator, SIGUSR2);
				sleep(DELAY);  // NOLINT(concurrency-mt-unsafe)
				kill(*iterator, SIGUSR1);
			}
		}
		else if (string[0u] == 'k')
		{
			T_CLASS(TConsole, print)(kOutput, "Killing THE CHOSEN children process...\n");
			const pid_t temp = pid_from_split(container, string, " k");
			if (temp == -1)
				T_CLASS(TConsole, print)(kError, "No such child pid...\n");
			else
				T_CLASS(TConsole, print)(kError, "FAILED...\n");
		}
		else if (string[0u] == 'm')
		{
			T_CLASS(TConsole, print)(kOutput, "Muting THE CHOSEN children process...\n");
			const pid_t temp = pid_from_split(container, string, " m");
			if (temp == -1)
				T_CLASS(TConsole, print)(kError, "No such child pid...\n");
			else kill(temp, SIGUSR1);
		}
		else if (string[0u] == 'u')
		{
			const pid_t temp = pid_from_split(container, string, " u");
			if (temp == -1)
				T_CLASS(TConsole, print)(kError, "No such child pid...\n");
			else kill(temp, SIGUSR2);
		}
		else if (string[0u] == 'p')
		{
			T_CLASS(TConsole, print)(kOutput, "Printing stats for THE CHOSEN children process...\n");
			const pid_t temp = pid_from_split(container, string, " p");
			if (temp == -1)
				T_CLASS(TConsole, print)(kError, "No such child pid...\n");
			else
			{
				kill(temp, SIGUSR2);
				sleep(DELAY);  // NOLINT(concurrency-mt-unsafe)
				kill(temp, SIGUSR1);
			}
		}
		else T_CLASS(TConsole, print)(kError, "No such command!\n");
		T_CLASS(TConsole, clear)();

		syscall__clear();
	}
}
