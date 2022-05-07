#pragma once

#include "../tipc.h"

#define T_IMPORT_SHARED_MEMORY_DECLARATION(T_SHARED_MEMORY_TYPE) \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, default_constructor)(void); \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, constructor)(const T_SHARED_MEMORY_TYPE value); \
	void T_IPC_SHM(T_SHARED_MEMORY_TYPE, write)(const TSharedMemory id, const T_SHARED_MEMORY_TYPE value); \
	T_SHARED_MEMORY_TYPE T_IPC_SHM(T_SHARED_MEMORY_TYPE, read)(const TSharedMemory id); \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, destructor)(const TSharedMemory id);

#define T_IMPORT_SHARED_MEMORY_DEFINITION(T_SHARED_MEMORY_TYPE) \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, default_constructor)(void) \
	{ \
		const TSharedMemory id = shmget(IPC_PRIVATE, sizeof(T_SHARED_MEMORY_TYPE), T_IPC_MODE | IPC_CREAT); \
		if (id < 0) T_THROW_EXCEPTION("TSharedMemory", "Functtion shmget failed to allocate shared memory", true, 0xCE001C0A,) \
		return id; \
	} \
	void T_IPC_SHM(T_SHARED_MEMORY_TYPE, write)(TSharedMemory id, const T_SHARED_MEMORY_TYPE value) \
	{ \
		T_SHARED_MEMORY_TYPE* memory = shmat(id, nullptr, 0); \
		(*memory) = value; \
		shmdt(memory); \
	} \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, constructor)(const T_SHARED_MEMORY_TYPE value) \
	{ \
		const TSharedMemory id = T_IPC_SHM(T_SHARED_MEMORY_TYPE, default_constructor)(); \
		T_IPC_SHM(T_SHARED_MEMORY_TYPE, write)(id, value); \
		return id; \
	} \
	T_SHARED_MEMORY_TYPE T_IPC_SHM(T_SHARED_MEMORY_TYPE, read)(TSharedMemory id) \
	{ \
		T_SHARED_MEMORY_TYPE* memory = shmat(id, nullptr, 0); \
		const T_SHARED_MEMORY_TYPE value = (*memory); \
		shmdt(memory); \
		return value; \
	} \
	TSharedMemory T_IPC_SHM(T_SHARED_MEMORY_TYPE, destructor)(TSharedMemory id) \
	{ \
		TSharedMemory result = shmctl(id, IPC_RMID, nullptr); \
		if (result < 0) T_THROW_EXCEPTION("TSharedMemory", "Functtion shmctl failed to deallocate shared memory", true, 0xCE001CDA,) \
		return result; \
	}
