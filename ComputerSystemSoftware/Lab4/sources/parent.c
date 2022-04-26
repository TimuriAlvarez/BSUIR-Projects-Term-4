#include "parent.h"

TBool vector_is_empty(T_CONTAINER(TVector, pid_t, Container) const container)
{
	const TBool result = T_CONTAINER(TVector, pid_t,is_empty)(container);
	if (result) T_CLASS(TConsole, print)(kError, "Sorry, but the vector of pids is empty. Try to add come children processes.\n");
	return result;
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
void top_bar(T_CONTAINER(TVector, pid_t, Container) const container)
{
	print_hint();
	size_t index = 0u;
	T_CLASS(TConsole, print)(kOutput, "> Parent processes ids:\n");
	T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", index, getpid());
	if (T_CONTAINER(TVector, pid_t, size)(container) != 0u)
		T_CLASS(TConsole, print)(kOutput, "> Children process ids:\n");
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
		T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", ++index, *iterator);
}

void kill_last(T_CONTAINER(TVector, pid_t, Container) const container, const TBool message)
{
	if (T_CONTAINER(TVector, pid_t, size)(container) == 0u) return;
	T_CONTAINER(TVector, pid_t, set_iteration_direction)(container, true);
	T_CONTAINER(TVector, pid_t, Iterator) iterator = T_CONTAINER(TVector, pid_t, Iterator_start)(container);
	const pid_t pid = *iterator;
	T_CONTAINER(TVector, pid_t, set_iteration_direction)(container, false);
		T_CONTAINER(TVector, pid_t, chop)(container, true);
	kill(pid, SIGINT);
	waitpid(pid, nullptr, 0);
	if (!message) return;
	T_CLASS(TConsole, print)(kOutput, "Process %i was killed.\n", pid);
	T_CLASS(TConsole, print)(kOutput, "%zu processes has left.\n", T_CONTAINER(TVector, pid_t, size)(container));
}
void kill_selected(T_CONTAINER(TVector, pid_t, Container) const container, const int index)
{
	if (index < 0)
	{
		T_CLASS(TConsole, print)(kError, "Invalid pid index!\n");
		return;
	}
	const pid_t pid = *T_CONTAINER(TVector, pid_t, at_index)(container, index);
	T_CLASS(TConsole, print)(kDebug, "pid: %d\n", pid);

	for (size_t i = (size_t)index; i < T_CONTAINER(TVector, pid_t, size)(container) - 1u; ++i)
		*T_CONTAINER(TVector, pid_t, at_index)(container, i) = *T_CONTAINER(TVector, pid_t, at_index)(container, i+1u);
	T_CONTAINER(TVector, pid_t, chop)(container, true);

	kill(pid, SIGINT);
	waitpid(pid, nullptr, 0);
	T_CLASS(TConsole, print)(kOutput, "Process %i was killed.\n", pid);
	T_CLASS(TConsole, print)(kOutput, "%zu processes has left.\n", T_CONTAINER(TVector, pid_t, size)(container));
}
void kill_all(T_CONTAINER(TVector, pid_t, Container) const container)
{
	const size_t size = T_CONTAINER(TVector, pid_t, size)(container);
	while (T_CONTAINER(TVector, pid_t, size)(container) != 0u)
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

int find_pid(T_CONTAINER(TVector, pid_t, Container) const container, const pid_t pid)
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
pid_t get_pid(T_CONTAINER(TVector, pid_t, Container) const container, TString message)
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
	if ((size_t)pid > T_CONTAINER(TVector, pid_t, size)(container))
	{
		T_CLASS(TConsole, print)(kError, "Provided index is out of range!\n");
		return FAILED;
	}
	return *T_CONTAINER(TVector, pid_t, at_index)(container, pid-1u);
}

void parent_handler(const int signal)
{
	int pid = 0;
	switch(signal)
	{
	case SIGUSR1:
		kill(pid, SIGUSR1);
		return;
	default:
		return;
	}
}
