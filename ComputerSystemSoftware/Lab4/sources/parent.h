#pragma once
#define T_DEBUG
#include "Lab4.h"

#define CONTAINER_DATA_TYPE pid_t
#include "../../../TlibLibraryC/TlibLibraryC/tcontainer/tvector.h"

TFlag vecotor_is_empty(TVector__pid_t__Container const container)
{
	const TFlag result = TVector__pid_t__is_empty(container);
	if (result) T_CLASS(TConsole, print)(kError, "Sorry, but the vector of pids is empty. Try to add come children processes.\n");
	return result;
}

void console_start(void)
{
	T_CLASS(TConsole, start)(nullptr, nullptr, nullptr, nullptr);
	T_CLASS(TConsole, set_format)(kInput, kNormal, true, kYellow);
	T_CLASS(TConsole, set_format)(kOutput, kNormal, true, kGreen);
	T_CLASS(TConsole, set_format)(kError, kNormal, true, kRed);
	T_CLASS(TConsole, set_format)(kLog, kNormal, true, kCyan);
	T_CLASS(TConsole, set_format)(kDebug, kNormal, true, kPurple);
}
void console_end(void)
{
	T_CLASS(TConsole, end)();
}
void pipe_end(void)
{
	close(PIPE_INPUT);
	close(PIPE_OUTPUT);
}

void print_hint(void)
{
	T_CLASS(TConsole, print)(kOutput, "> Available commands:\n");
	T_CLASS(TConsole, print)(kInput, "+\t: Add new child;\n");
	T_CLASS(TConsole, print)(kInput, "-\t: Kill last added child;\n");
	T_CLASS(TConsole, print)(kInput, "k (pid) : Kill the child with pid;\n");
	T_CLASS(TConsole, print)(kInput, "m (pid) : Mute the child with pid;\n");
	T_CLASS(TConsole, print)(kInput, "u (pid) : Unmmute the child with pid;\n");
	T_CLASS(TConsole, print)(kInput, "p (pid) : Print stats for the child with pid;\n");
	T_CLASS(TConsole, print)(kInput, "q\t: Quit the program.\n\n");
	T_CLASS(TConsole, print)(kOutput, "> Hint:\n");
	T_CLASS(TConsole, print)(kInput, "(pid)\t: If no pid was provided - apply to all children's pids.\n");
	T_CLASS(TConsole, print)(kOutput, "\n");
}
void top_bar(TVector__pid_t__Container const container)
{
	print_hint();
	size_t index = 0u;
	T_CLASS(TConsole, print)(kOutput, "> Parent processes ids:\n");
	T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", index, getpid());
	if (container->size != 0u)
		T_CLASS(TConsole, print)(kOutput, "> Children process ids:\n");
	for (TVector__pid_t__Iterator iterator = TVector__pid_t__Iterator_start(container);
		iterator != TVector__pid_t__Iterator_end();
		iterator = TVector__pid_t__Iterator_iterate(container, iterator))
		T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", ++index, *iterator);
}

void kill_last(TVector__pid_t__Container const container, const TFlag message)
{
	if (container->size == 0u) return;
	container->reversed_iteration = true;
	TVector__pid_t__Iterator iterator = TVector__pid_t__Iterator_start(container);
	const pid_t pid = *iterator;
	container->reversed_iteration = false;
	TVector__pid_t__chop(container, true);
	kill(pid, SIGINT);
	waitpid(pid, nullptr, 0);
	if (!message) return;
	T_CLASS(TConsole, print)(kOutput, "Process %i was killed.\n", pid);
	T_CLASS(TConsole, print)(kOutput, "%zu processes has left.\n", container->size);
}
void kill_selected(TVector__pid_t__Container const container, const int index)
{
	if (index <0)
	{
		T_CLASS(TConsole, print)(kError, "Invalid pid index!\n");
		return;
	}
	const pid_t pid = container->data[index];
	T_CLASS(TConsole, print)(kDebug, "pid: %d\n", pid);

	for (size_t i = (size_t)index; i < container->size - 1u; ++i)
		container->data[i] = container->data[i+1u];
	TVector__pid_t__chop(container, true);

	kill(pid, SIGINT);
	waitpid(pid, nullptr, 0);
	T_CLASS(TConsole, print)(kOutput, "Process %i was killed.\n", pid);
	T_CLASS(TConsole, print)(kOutput, "%zu processes has left.\n", container->size);
}
void kill_all(TVector__pid_t__Container const container)
{
	const size_t size = container->size;
	while (container->size != 0u)
		kill_last(container, false);
	T_CLASS(TConsole, print)(kOutput, "%zu process(es) was(were) killed.\nNo processes have left.\n", size);
}

//returns number that located int the end of line or 0 if no number where found
int ParseIntFromEnd(TMessage line)
{
	//find end of line
	int end_line = 0;
	for(int i = 0; line[i] != '\0';i++)
		end_line = i;
	int return_int = 0; //converting;
	int pos = 0, temp;
	for(int i = end_line; i > 0; i--)
	{
		if(!((line[i] >= '0' && line[i] <='9') || line[i] == '-')) break;
		if(line[i] == '-')
		{
			return_int*=-1;
			return return_int;
		}
		temp = line[i]-48;
		for(int j = 0;j < pos; j++)
			temp*=10;
		pos++;
		return_int+=temp;
	}
	return return_int;
}

int find_pid(TVector__pid_t__Container const container, const pid_t pid)
{
	int index = 0;
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
	{
		if (*iterator == pid)
			return index;
		++index;
	}
	return -1;
}
pid_t get_pid(TVector__pid_t__Container const container, TString message)
{
	static const pid_t FAILED = -1;
	if (message == nullptr) return FAILED;
	pid_t pid = ParseIntFromEnd(message);
	if (pid >= 0)
	{
		if (find_pid(container, pid) != -1) return pid;
		T_CLASS(TConsole, print)(kError, "There is no child with provided pid!\n");
		return FAILED;
	}
	pid *= -1;
	if ((size_t)pid > container->size)
	{
		T_CLASS(TConsole, print)(kError, "Provided index is out of range!\n");
		return FAILED;
	}
	return container->data[pid-1];
}

void parent_handler(const int signal)
{
	int buffer = PRINT_PROCESS;
	int pid;
	switch(signal)
	{
	case SIGUSR1:
		read(PIPE_OUTPUT, &pid, sizeof(int));
		write(PIPE_INPUT, &buffer, sizeof(int));
		kill(pid, SIGUSR1);
		sleep(0);
		return;
	default:
		return;
	}
}
