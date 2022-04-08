#include "parent.h"
#include "child.h"
#include <errno.h>

#define DELAY 1

int main(void)
{
	struct sigaction sigaction_handler;
	sigaction_handler.sa_handler = parent_handler;
	sigaction(SIGUSR1, &sigaction_handler, nullptr);

	syscall__clear();
	console_start();
	register_at_exit(console_end);
	TVector__pid_t__Container const container = TVector__pid_t__constructor();

	if (pipe(process_pipe) < 0)
	{
		TException exception = {nullptr, E_LOCATION, 0, 0, true};
		t_exception(exception);
	}
	register_at_exit(pipe_end);

	int buffer;
	TString string = TString__constructor();
	while (true)
	{
		top_bar(container);
		T_CLASS(TString, clear)(string);
		T_CLASS(TConsole, print)(kOutput, "> ");
		string = T_CLASS(TConsole, getline)(nullptr, true);
		//	Empty string
		if (T_CLASS(TMessage, empty)(string))
		{
			syscall__clear();
			continue;
		}
		//	Quit the programm
		if (T_CLASS(TMessage, equal)(string, "q"))
		{
			T_CLASS(TConsole, print)(kOutput, "Quitting...\n");
			kill_all(container);
			TVector__pid_t__destructor(container);
			T_CLASS(TString, destructor)(string);
			return 0;
		}
		//	Add a child
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
		else if (!vecotor_is_empty(container))
		{
			//	Kill the last child
			if (T_CLASS(TMessage, equal)(string, "-"))
			{
				T_CLASS(TConsole, print)(kOutput, "Killing the last added child...\n");
				kill_last(container, true);
			}
			//	Kill all children
			else if (T_CLASS(TMessage, equal)(string, "k"))
			{
				T_CLASS(TConsole, print)(kOutput, "Killing all children processes...\n");
				kill_all(container);
			}
			//	Mute all children
			else if (T_CLASS(TMessage, equal)(string, "m"))
			{
				T_CLASS(TConsole, print)(kOutput, "Muting all children processes...\n");
				buffer = MUTE_PROCESS;
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
				{
					write(PIPE_INPUT, &buffer, sizeof(int));
					kill(*iterator, SIGUSR1);
				}
				T_CLASS(TConsole, print)(kOutput, "All children processes are muted.\n");
			}
			//	Unmute all children
			else if (T_CLASS(TMessage, equal)(string, "u"))
			{
				T_CLASS(TConsole, print)(kOutput, "Unmuting all children processes...\n");
				buffer = UNMUTE_PROCESS;
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
				{
					write(PIPE_INPUT, &buffer, sizeof(int));
					kill(*iterator, SIGUSR1);
				}
				T_CLASS(TConsole, print)(kOutput, "All children processes are unmuted.\n");
			}
			//	Print stats for all children
			else if (T_CLASS(TMessage, equal)(string, "p"))
			{
				T_CLASS(TConsole, print)(kOutput, "Printing stats for all children process...\n");
				buffer = PRINT_PROCESS;
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
				{
					buffer = *iterator;
					write(PIPE_INPUT, &buffer, sizeof(int));
					raise(SIGUSR1);
				}
				T_CLASS(TConsole, echo)(false);
				sleep(DELAY);
				T_CLASS(TConsole, echo)(true);
				T_CLASS(TConsole, print)(kOutput, "Done.\n");
			}
			else if (string[1u] == ' ')
			{
				const pid_t pid = get_pid(container, string);
				if (pid != -1) switch (string[0u])
				{
				case 'k':
					T_CLASS(TConsole, print)(kOutput, "Killing %d processes...\n", pid);
					T_CLASS(TConsole, print)(kDebug, "Index of pid: %d\n", find_pid(container, pid));
					kill_selected(container, find_pid(container, pid));
					break;
				case 'm':
					T_CLASS(TConsole, print)(kOutput, "Muting %d processes...\n", pid);
					buffer = MUTE_PROCESS;
					write(PIPE_INPUT, &buffer, sizeof(int));
					kill(pid, SIGUSR1);
					T_CLASS(TConsole, print)(kOutput, "Processes %d is muted.\n", pid);
					break;
				case 'u':
					T_CLASS(TConsole, print)(kOutput, "Unmuting %d processes...\n", pid);
					buffer = UNMUTE_PROCESS;
					write(PIPE_INPUT, &buffer, sizeof(int));
					kill(pid, SIGUSR1);
					T_CLASS(TConsole, print)(kOutput, "Processes %d is unmuted.\n", pid);
					break;
				case 'p':
					T_CLASS(TConsole, print)(kOutput, "Printing stats for %d process...\n", pid);
					buffer = pid;
					write(PIPE_INPUT, &buffer, sizeof(int));
					raise(SIGUSR1);
					/*
					buffer = PRINT_PROCESS;
					write(PIPE_INPUT, &buffer, sizeof(int));
					kill(pid, SIGUSR1);
					sleep(DELAY);*/
					T_CLASS(TConsole, print)(kOutput, "Done.\n");
					break;
				default:
					T_CLASS(TConsole, print)(kError, "Invalid command!\n");
					break;
				}
			}
			else T_CLASS(TConsole, print)(kError, "Invalid command!\n");
		}
		syscall__update();
	}
}
