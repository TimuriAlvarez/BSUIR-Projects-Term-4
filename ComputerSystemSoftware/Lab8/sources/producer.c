#include "thread.h"
#include <pthread.h>
#include <unistd.h>

thread kill_producer_tid = 0;
extern T_CONTAINER(TList, Circle, T_CONTAINER_POSTFIX) circles;
extern T_CONTAINER(TVector, thread, T_CONTAINER_POSTFIX) producers;

void* producer_sycle(void* pointer)
{
	while(true) FOR_EACH_ITERATOR_FROM(iterator, TList, Circle, circles)
	{
		if (pthread_self() == kill_producer_tid) pthread_exit(pointer);
		produce_message(iterator);
		sched_yield();
		sleep(T_DELAY);
	}
}

void add_producer(void)
{
	thread thread;
	int status = pthread_create(&thread, nullptr, producer_sycle, nullptr);
	if (status == 0) T_RETURN_VOID(T_CONTAINER(TVector, thread, append)(producers, thread, true);)
	destroy_producers();
	T_THROW_EXCEPTION("Threads", "Function 'pthread_create' failed to create a new thread correctly", true, 0xCE00011E, return;)
}
void kill_producer(void)
{
	if (T_CONTAINER(TVector, thread, is_empty)(producers)) T_RETURN_VOID(T_CLASS(TConsole, print)(kError, "No producers to kill!\n");)
	pthread_join(kill_producer_tid = *T_CONTAINER(TVector, thread, at_index)(producers, T_CONTAINER(TVector, thread, size)(producers) - 1), nullptr);
	T_CONTAINER(TVector, thread, chop)(producers, true);
}
void destroy_producers(void)
{
	while (!T_CONTAINER(TVector, thread, is_empty)(producers)) kill_producer();
	T_CONTAINER(TVector, thread, destructor)(producers);
}
