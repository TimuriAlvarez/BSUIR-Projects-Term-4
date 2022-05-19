#include "tlib.h"

TMutex lock;
T_CONTAINER(TList, Circle, T_CONTAINER_POSTFIX) circles;
T_CONTAINER(TVector, thread, T_CONTAINER_POSTFIX) producers;
T_CONTAINER(TVector, thread, T_CONTAINER_POSTFIX) takers;

int main(void)
{
	T_CLASS(TConsole, debug)(true);
	lock = T_CLASS(TMutex, default_constructor)();
	circles = T_CONTAINER(TList, Circle, constructor)();
	producers = T_CONTAINER(TVector, thread, default_constructor)();
	takers = T_CONTAINER(TVector, thread, default_constructor)();
	TString get_line = T_CLASS(TString, default_constructor)();
	while(true)
	{
		T_CLASS(TMutex, lock)(lock);
		T_FUNCTION(syscall, clear)();
		T_CLASS(TConsole, print)(kOutput, "Menu options:\n"
										  "\t c)\tAllocate memory for circle;\n"
										  "\t s)\tShow statistic for circles;\n"
										  "\t p)\tCreate one more producer-thread;\n"
										  "\t t)\tCreate one more taker-thread;\n"
										  "\t f)\tFree run (let producers/takers do their jobs);\n"
										  "\t-p)\tKill last created producer-thread;\n"
										  "\t-t)\tKill last created taker-thread;\n"
										  "\t q)\tQuit programm.\n"
										  "Choose the option: ");
		T_CLASS(TString, destructor)(get_line);
		get_line = T_CLASS(TConsole, getline)(nullptr, true);
		T_CLASS(TMutex, unlock)(lock);
		if (T_CLASS(TString, empty)(get_line)) continue;
		if (T_CLASS(TString, equal)(get_line, "q"))
		{
			T_CLASS(TMutex, lock)(lock);
			T_CLASS(TConsole, print)(kLog, "Finishing all threads... It may take a wile.\n");
			T_CLASS(TMutex, unlock)(lock);
			break;
		}
		if (T_CLASS(TString, equal)(get_line, "f")) {}
		elif (T_CLASS(TString, equal)(get_line, "c")) append_circle();
		elif (T_CLASS(TString, equal)(get_line, "s")) print_circle();
		elif (T_CLASS(TString, equal)(get_line, "p")) add_producer();
		elif (T_CLASS(TString, equal)(get_line, "t")) add_taker();
		elif (T_CLASS(TString, equal)(get_line, "-p")) kill_producer();
		elif (T_CLASS(TString, equal)(get_line, "-t")) kill_taker();
		else T_CLASS(TConsole, print)(kError, "No such option.\n");
		T_FUNCTION(syscall, pause)();
	}
	destroy_producers();
	destroy_takers();
	free_circle();
	T_CLASS(TMutex, destructor)(lock);
	T_CLASS(TString, destructor)(get_line);
	return 0;
}
