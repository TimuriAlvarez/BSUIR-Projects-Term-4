#pragma once

#include "tmux.h"

#include <pthread.h>

T_IMPORT_MEMORY_DEFINITION(pthread_mutex_t)

TMutex T_CLASS(TMutex, default_constructor)(void)
{
	TMutex mutex = T_MEMORY_MANAGER(allocate, pthread_mutex_t)(1u);
	if (pthread_mutex_init(mutex, nullptr) != 0)
		T_THROW_EXCEPTION("TMutex", nullptr, true, 0x00, )
	return mutex;
}
TMutex T_CLASS(TMutex, constructor)(void)
{
	return T_CLASS(TMutex, default_constructor)();
}
TMutex T_CLASS(TMutex, destructor)(TMutex const mutex)
{
	return T_MEMORY_MANAGER(deallocate, pthread_mutex_t)(mutex);
}

void T_CLASS(TMutex, lock)(TMutex const mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		T_THROW_EXCEPTION("TMutex", nullptr, true, 0x00, )
}
TBool T_CLASS(TMutex, try_lock)(TMutex const mutex)
{
	if (pthread_mutex_trylock(mutex) == 0) return true;
	return false;
}
void T_CLASS(TMutex, unlock)(TMutex const mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		T_THROW_EXCEPTION("TMutex", nullptr, true, 0x00, )
}
