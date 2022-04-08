// ReSharper disable CppClangTidyMiscMisplacedConst
#pragma once

#include "Lab4.h"
#define CONTAINER_DATA_TYPE pid_t
#include "../../../Tlib Library C/Tlib Library C/tcontainer/tvector.h"

void console_start(void)
{
	T_CLASS(TConsole, start)(nullptr, nullptr, nullptr, nullptr);
	T_CLASS(TConsole, set_format)(kInput, kNormal, true, kYellow);
	T_CLASS(TConsole, set_format)(kOutput, kNormal, true, kGreen);
	T_CLASS(TConsole, set_format)(kError, kNormal, true, kRed);
	T_CLASS(TConsole, set_format)(kLog, kNormal, true, kCyan);
}
void console_end(void)
{
	T_CLASS(TConsole, end)();
}

void print_hint(void)
{
	T_CLASS(TConsole, print)(kOutput, "Available commands:\n");
	T_CLASS(TConsole, print)(kInput, "+      : add a child\t");
	T_CLASS(TConsole, print)(kInput, "u (pid): unmute pid\t");
	T_CLASS(TConsole, print)(kInput, "k (pid): kill pid\n");
	T_CLASS(TConsole, print)(kInput, "-      : kill last one\t");
	T_CLASS(TConsole, print)(kInput, "m (pid): mute pid\t");
	T_CLASS(TConsole, print)(kInput, "q      : kill all and quit\t\n");
	T_CLASS(TConsole, print)(kInput, "Hint: if no (pid) was provided: applying to all pids.\n");
}
void top_bar(TVector__pid_t__Container const container)
{
	print_hint();
	size_t index = 0u;
	T_CLASS(TConsole, print)(kOutput, "Parent process id:\n");
	T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", index, getpid());
	if (container->size != 0u)
		T_CLASS(TConsole, print)(kOutput, "Children process ids:\n");
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pid_t, container)
		T_CLASS(TConsole, print)(kInput, "\t%zu\t%i\n", ++index, *iterator);
}

void kill_last(TVector__pid_t__Container const container, const TFlag message)
{
	if (container->size == 0u) return;
	const pid_t pid = container->data[container->size - 1u];
	TVector__pid_t__chop(container, /*1,*/ true);
	kill(pid, SIGINT);
	waitpid(pid, nullptr, 0);
	if (!message) return;
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

pid_t int_2_pid(TVector__pid_t__Container const container, const int value)
{
	if (value >= 0) return (pid_t)value;
	if ((size_t)(-value) > container->size)
	{
		/*	TODO: EXCEPTION	*/
		T_CLASS(TConsole, print)(kError, "Out of array range!\n");
		return -1;
	}
	return container->data[-1 - value];
}
pid_t pid_from_split(TVector__pid_t__Container const container, TMessage string, TMessage splitters)
{
	TString* split = TMessage__split(string, splitters, false);
	if (split[0u] == nullptr || split[1u] != nullptr)
	{
		T_CLASS(TConsole, print)(kError, "Invalid number of characters!\n");
		return -1;
	}

	const int value = T_CONVERTER(TMessage, int)(split[1u]);

	for (size_t i = 0u; split[i] != nullptr; ++i)
		T_FUNCTION(delete, char)(split[i]);
	T_FUNCTION(delete, TString)(split);

	return int_2_pid(container, value);
}
