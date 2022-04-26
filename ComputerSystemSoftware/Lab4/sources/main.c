#include "tlib.h"

#include "parent.h"
#include "child.h"
#include "memory.h"

#define DELAY 1

#define T_THROW_BADFORK T_THROW_EXCEPTION("Fork", "Fork failed to start a child process", true, 0xCE0100,)

SharedMemory memory;

void shmem_clear(void)
{
	memory = T_CLASS(SharedMemory, destructor)(memory);
}

int main(void)
{
	T_FUNCTION(syscall, clear)();
	struct sigaction sigaction_handler;
	sigaction_handler.sa_handler = parent_handler;
	sigaction(SIGUSR1, &sigaction_handler, nullptr);

	memory = T_CLASS(SharedMemory, constructor)();
	T_FUNCTION(syscall, atexit)(shmem_clear);

	T_CONTAINER(TVector, pid_t, Container) container = T_CONTAINER(TVector, pid_t, default_constructor)();

	TString string = T_CLASS(TString, default_constructor)();
	while (true)
	{
		top_bar(container);
		T_CLASS(TString, clear)(string);
		T_CLASS(TConsole, print)(kOutput, "> ");
		string = T_CLASS(TConsole, getline)(nullptr, true);
		//	Empty string
		if (T_CLASS(TString, empty)(string))
		{
			T_FUNCTION(syscall, clear)();
			continue;
		}
		//	Quit the programm
		if (T_CLASS(TString, equal)(string, "q"))
		{
			T_CLASS(TConsole, print)(kOutput, "Quitting...\n");
			kill_all(container);
			T_CONTAINER(TVector, pid_t, destructor)(container);
			T_CLASS(TString, destructor)(string);
			return 0;
		}
		//	Add a child
		if (T_CLASS(TString, equal)(string, "+"))
		{
			T_CLASS(TConsole, print)(kOutput, "Adding a child...\n");
			const pid_t pid = fork();
			if (pid == -1) T_THROW_BADFORK
			if (pid == 0) child_function();
			T_CONTAINER(TVector, pid_t, append)(container, pid, true);
			T_CLASS(TConsole, print)(kOutput, "Child process %i was created\n", pid);
		}
		else if (!vector_is_empty(container))
		{
			//	Kill the last child
			if (T_CLASS(TString, equal)(string, "-"))
			{
				T_CLASS(TConsole, print)(kOutput, "Killing the last added child...\n");
				kill_last(container, true);
			}
			//	Kill all children
			else if (T_CLASS(TString, equal)(string, "k"))
			{
				T_CLASS(TConsole, print)(kOutput, "Killing all children processes...\n");
				kill_all(container);
			}
			//	Mute all children
			else if (T_CLASS(TString, equal)(string, "m"))
			{
				T_CLASS(TConsole, print)(kOutput, "Muting all children processes...\n");
				T_CLASS(SharedMemory, write)(memory, SHMEM_MUTE_PROCESS);
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
						kill(*iterator, SIGUSR1);
				T_CLASS(TConsole, print)(kOutput, "All children processes are muted.\n");
			}
			//	Unmute all children
			else if (T_CLASS(TString, equal)(string, "u"))
			{
				T_CLASS(TConsole, print)(kOutput, "Unmuting all children processes...\n");
				T_CLASS(SharedMemory, write)(memory, SHMEM_UNMUTE_PROCESS);
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
						kill(*iterator, SIGUSR1);
				T_CLASS(TConsole, print)(kOutput, "All children processes are unmuted.\n");
			}
			//	Print stats for all children
			else if (T_CLASS(TString, equal)(string, "p"))
			{
				T_CLASS(TConsole, print)(kOutput, "Printing stats for all children process...\n");
				FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
				{
					T_CLASS(SharedMemory, write)(memory, *iterator);
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
					kill(pid, SIGUSR1);
					T_CLASS(TConsole, print)(kOutput, "Processes %d is muted.\n", pid);
					break;
				case 'u':
					T_CLASS(TConsole, print)(kOutput, "Unmuting %d processes...\n", pid);
					kill(pid, SIGUSR1);
					T_CLASS(TConsole, print)(kOutput, "Processes %d is unmuted.\n", pid);
					break;
				case 'p':
					T_CLASS(TConsole, print)(kOutput, "Printing stats for %d process...\n", pid);
					raise(SIGUSR1);
					T_CLASS(TConsole, print)(kOutput, "Done.\n");
					break;
				default:
					T_CLASS(TConsole, print)(kError, "Invalid command!\n");
					break;
				}
			}
			else T_CLASS(TConsole, print)(kError, "Invalid command!\n");
		}
		T_FUNCTION(syscall, update)();
	}
}
