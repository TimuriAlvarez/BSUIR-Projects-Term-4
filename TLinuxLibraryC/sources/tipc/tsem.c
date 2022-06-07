#pragma once

#include "tsem.h"

#include <semaphore.h>

typedef sem_t* TSemaphorePointer;

typedef struct TSemaphoreAllocator
{
	TString name;
	TSemaphorePointer pointer;
} TSemaphoreAllocator;

T_IMPORT_MEMORY_DEFINITION(TSemaphoreAllocator)

#define T_IPC_VALIDATE(T_VALUE) if (T_VALUE) T_THROW_EXCEPTION

TSemaphore T_CLASS(TSemaphore, open)(TMessage name)
{
	TString real_name = T_CLASS(TString, constructor)("/%s", name);
	TSemaphorePointer pointer = sem_open(real_name, 0);
	if (pointer == SEM_FAILED)
		T_THROW_EXCEPTION("TSemaphore", nullptr, false, 0x00,
						  {
							  real_name = T_CLASS(TString, destructor)(real_name);
							  return nullptr;
						  } )
	TSemaphore result = T_MEMORY_MANAGER(TSemaphoreAllocator, allocate)(1);
	result->name = real_name;
	result->pointer = pointer;
	return result;
}
TSemaphore T_CLASS(TSemaphore, close)(TSemaphore semaphore)
{
	if (semaphore->pointer != nullptr)
		T_IPC_VALIDATE(sem_close(semaphore->pointer))("TSemaphore", nullptr, false, 0x00, return semaphore; )
	semaphore->name = T_CLASS(TString, destructor)(semaphore->name);
	semaphore->pointer = nullptr;
	return semaphore;
}

TSemaphore T_CLASS(TSemaphore, constructor)(TMessage name, const uint default_value)
{
	TString real_name = T_CLASS(TString, constructor)("/%s", name);
	TSemaphorePointer pointer = sem_open(name, O_CREAT | O_EXCL, T_IPC_MODE, default_value);
	if (pointer == SEM_FAILED)
		T_THROW_EXCEPTION("TSemaphore", nullptr, false, 0x00,
						  {
							  real_name = T_CLASS(TString, destructor)(real_name);
							  return nullptr;
						  } )
	TSemaphore result = T_MEMORY_MANAGER(TSemaphoreAllocator, allocate)(1);
	result->name = real_name;
	result->pointer = pointer;
	return result;
}
TSemaphore T_CLASS(TSemaphore, default_constructor)(TMessage name)
{
	return T_CLASS(TSemaphore, constructor)(name, 0u);
}
TSemaphore T_CLASS(TSemaphore, destructor)(TSemaphore semaphore)
{
	TString name = semaphore->name; semaphore->name = nullptr;
	T_CLASS(TSemaphore, close)(semaphore);
	T_IPC_VALIDATE(sem_unlink(name))("TSemaphore", nullptr, false, 0x00,)
	semaphore->name = T_CLASS(TString, destructor)(name);
	return T_MEMORY_MANAGER(TSemaphoreAllocator, deallocate)(semaphore);;
}

uint T_CLASS(TSemaphore, get_value)(TSemaphore semaphore)
{
	if (semaphore->pointer == nullptr) return 0u;
	int value;
	sem_getvalue(semaphore->pointer, &value);
	return value;
}
void T_CLASS(TSemaphore, increment)(TSemaphore semaphore)
{
	if (semaphore->pointer == nullptr) return;
	sem_post(semaphore->pointer);
}
void T_CLASS(TSemaphore, decrement)(TSemaphore semaphore)
{
	if (semaphore->pointer == nullptr) return;
	sem_wait(semaphore->pointer);
}

T_IMPORT_MATH_DEFINITION(uint)
void T_CLASS(TSemaphore, set_value)(TSemaphore semaphore, const uint value)
{
	while (true) switch (T_FUNCTION(compare, uint)(T_CLASS(TSemaphore, get_value)(semaphore), value))
	{
	case kEqual:
		return;
	case kLess:
		T_CLASS(TSemaphore, increment)(semaphore);
		break;
	case kGreater:
		T_CLASS(TSemaphore, increment)(semaphore);
		break;
	}
}
