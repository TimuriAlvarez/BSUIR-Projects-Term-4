#pragma once

#include "tmux.h"

#include <pthread.h>

T_IMPORT_MEMORY_DEFINITION(pthread_mutex_t)

TMutex T_CLASS(TMutex, default_constructor)(void)
{
	TMutex mutex = T_MEMORY_MANAGER(allocate, pthread_mutex_t)(1u);
	if (pthread_mutex_init(mutex, nullptr) != 0)
		T_THROW_EXCEPTION("TMutex", nullptr)
}
TMutex T_CLASS(TMutex, constructor)(void)
{
	return T_CLASS(TMutex, default_constructor)();
}
TMutex T_CLASS(TMutex, destructor)(TMutex mutex)
{
	return T_MEMORY_MANAGER(deallocate, pthread_mutex_t)(mutex);
}

void T_CLASS(TMutex, lock)(TMutex mutex)
{

}
void T_CLASS(TMutex, unlock)(TMutex mutex)
{

}
