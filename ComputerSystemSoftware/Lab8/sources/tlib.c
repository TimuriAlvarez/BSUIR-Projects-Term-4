#include "tlib.h"

#include "../../../TLibLibraryC/tlib.c"

#define CONTAINER_DATA_TYPE pthread_t
#include "../../../TContainersC/timport/tvector.c"
#define CONTAINER_DATA_TYPE uint
#include "../../../TContainersC/timport/tvector.c"

TBool vector_is_empty(T_CONTAINER(TVector, pthread_t, Container) const container)
{
	const TBool result = T_CONTAINER(TVector, pthread_t,is_empty)(container);
	if (result) T_CLASS(TConsole, print)(kError, "Sorry, but the vector of pids is empty. Try to add come threads threads.\n");
	return result;
}

void print_hint(void)
{
	T_CLASS(TConsole, print)(kOutput, "> Available commands:\n");
	T_CLASS(TConsole, print)(kInput, "+\t: Add new thread;\n");
	T_CLASS(TConsole, print)(kInput, "-\t: Kill last added thread;\n");
	T_CLASS(TConsole, print)(kInput, "k       : Kill all threads;\n");
	T_CLASS(TConsole, print)(kInput, "m (pid) : Mute the thread with pid;\n");
	T_CLASS(TConsole, print)(kInput, "u (pid) : Unmmute the thread with pid;\n");
	T_CLASS(TConsole, print)(kInput, "p (pid) : Print stats for the thread with pid;\n");
	T_CLASS(TConsole, print)(kInput, "q\t: Quit the program.\n\n");
	T_CLASS(TConsole, print)(kOutput, "> Hint:\n");
	T_CLASS(TConsole, print)(kInput, "(pid)\t: If no pid was provided - apply to all threads' pids.\n");
	T_CLASS(TConsole, print)(kOutput, "\n");
}
void top_bar(T_CONTAINER(TVector, pthread_t, Container) const container)
{
	print_hint();
	size_t index = 0u;
	T_CLASS(TConsole, print)(kOutput, "> Parent threads ids:\n");
	T_CLASS(TConsole, print)(kInput, "\t%zu\t%lu\n", index, pthread_self());
	if (T_CONTAINER(TVector, pthread_t, size)(container) != 0u)
		T_CLASS(TConsole, print)(kOutput, "> Children threads ids:\n");
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pthread_t, container)
		T_CLASS(TConsole, print)(kInput, "\t%zu\t%lu\n", ++index, *iterator);
}
