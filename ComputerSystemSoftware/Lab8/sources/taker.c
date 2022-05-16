#include "thread.h"
#include <pthread.h>
#include <unistd.h>

thread kill_taker_tid = 0;
extern T_CONTAINER(TList, Circle, T_CONTAINER_POSTFIX) circles;
extern T_CONTAINER(TVector, thread, T_CONTAINER_POSTFIX) takers;

void* taker_sycle(void* pointer)
{
	while(true) FOR_EACH_ITERATOR_FROM(iterator, TList, Circle, circles)
	{
		if (pthread_self() == kill_taker_tid) pthread_exit(pointer);
		take_message(iterator);
		sched_yield();
		sleep(T_DELAY);
	}
}

void add_taker(void)
{
	thread thread;
	int status = pthread_create(&thread, nullptr, taker_sycle, nullptr);
	if (status == 0) T_RETURN_VOID(T_CONTAINER(TVector, thread, append)(takers, thread, true);)
	destroy_takers();
	T_THROW_EXCEPTION("Threads", "Function 'pthread_create' failed to create a new thread correctly", true, 0xCE00011E, return;)
}
void kill_taker(void)
{
	if (T_CONTAINER(TVector, thread, is_empty)(takers)) T_RETURN_VOID(T_CLASS(TConsole, print)(kError, "No takers to kill!\n");)
	pthread_join(kill_taker_tid = *T_CONTAINER(TVector, thread, at_index)(takers, T_CONTAINER(TVector, thread, size)(takers) - 1), nullptr);
	T_CONTAINER(TVector, thread, chop)(takers, true);
}
void destroy_takers(void)
{
	while (!T_CONTAINER(TVector, thread, is_empty)(takers)) kill_taker();
	T_CONTAINER(TVector, thread, destructor)(takers);
}
