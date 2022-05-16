#include "circle.h"
#include <pthread.h>

extern TMutex lock;
extern T_CONTAINER(TList, Circle, T_CONTAINER_POSTFIX) circles;

void append_circle(void)
{
	T_CLASS(TMutex, lock)(lock);
	static Circle default_value = { nullptr, 0u, 0u, 0u };
	T_CONTAINER(TList, Circle, push)(circles, default_value, true);
	T_CLASS(TMutex, unlock)(lock);
}
void print_circle(void)
{
	T_CLASS(TMutex, lock)(lock);
	if (T_CONTAINER(TList, Circle, is_empty)(circles)) T_RETURN_VOID(T_CLASS(TConsole, print)(kError, "The circle is empty!\n");)
	T_CLASS(TConsole, print)(kLog, "------------------------------------------------------\n");
	FOR_EACH_ITERATOR_FROM(iterator, TList, Circle, circles)
	{
		T_CLASS(TConsole, print)(kLog, "Address:\t0x%X\nAdded:\t\t%d\nRemoved:\t%d\nCheksum:\t%lld\n", iterator, iterator->added, iterator->deleted, iterator->checksum);
		T_CLASS(TConsole, print)(kLog, "------------------------------------------------------\n");
	}
	T_CLASS(TMutex, unlock)(lock);
}
void free_circle(void)
{
	T_CLASS(TMutex, lock)(lock);
	FOR_EACH_ITERATOR_FROM(iterator, TList, Circle, circles)
		T_CLASS(TString, destructor)(iterator->message);
	T_CONTAINER(TList, Circle, destructor)(circles);
	T_CLASS(TMutex, unlock)(lock);
}

void produce_message(T_CONTAINER(TList, Circle, T_ITERATOR_POSTFIX) const iterator)
{
	if (iterator == nullptr) return;
	T_CLASS(TMutex, lock)(lock);
	if (iterator->message != nullptr) T_RETURN_VOID(T_CLASS(TMutex, unlock)(lock););
	//creating message
	int size = rand() % 255;
	for(int i = 0; i < size;i++)
		iterator->message = T_CLASS(TString, append)(iterator->message, 'a' + rand() % ('z' - 'a' + 1));
	//creating checksum
	for(int i = 0; i < size; i++)
	{
		int num = iterator->message[i];
		iterator->checksum = iterator->checksum + num * i;
	}
	iterator->added++;
	T_CLASS(TConsole, print)(kInput, "Produser %lu setted message\n", pthread_self());
	T_CLASS(TMutex, unlock)(lock);
}
void take_message(T_CONTAINER(TList, Circle, T_ITERATOR_POSTFIX) const iterator)
{
	if (iterator == nullptr) return;
	T_CLASS(TMutex, lock)(lock);
	if (iterator->message == nullptr) T_RETURN_VOID(T_CLASS(TMutex, unlock)(lock););
	ullint check_checksum = 0;
	for(int i = 0; iterator->message[i] != '\0'; i++)
	{
		int num = iterator->message[i];
		check_checksum = check_checksum + num * i;
	}
	if(check_checksum != iterator->checksum) T_CLASS(TConsole, print)(kError, "Checksum wasnt correct!\n");
	T_CLASS(TConsole, print)(kInput, "Taker %lu read: %s\n", pthread_self(), iterator->message);
	iterator->message = T_CLASS(TString, destructor)(iterator->message);
	iterator->checksum = 0;
	iterator->deleted++;
	T_CLASS(TMutex, unlock)(lock);
}
