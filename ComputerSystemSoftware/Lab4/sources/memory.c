#include "memory.h"
#include <sys/shm.h>

#define T_LENGTH sizeof(int)

SharedMemoryID T_CLASS(SharedMemory, constructor)(void)
{
	const SharedMemoryID id = shmget(IPC_PRIVATE, sizeof(int), 0666 | IPC_CREAT);
	if (id < 0) T_THROW_EXCEPTION("SharedMemory", "Functtion shmget failed to allocate shared memory", true, 0xCE00015C,)
	return id;
}

void T_CLASS(SharedMemory, write)(SharedMemoryID id, int value)
{
	SharedMemory memory = shmat(id, nullptr, 0);
	(*memory) = value;
	shmdt(memory);
}

int T_CLASS(SharedMemory, read)(SharedMemoryID id)
{
	SharedMemory memory = shmat(id, nullptr, 0);
	const int value = (*memory);
	shmdt(memory);
	return value;
}

SharedMemoryID T_CLASS(SharedMemory, destructor)(SharedMemoryID id)
{
	SharedMemoryID result = shmctl(id, IPC_RMID, nullptr);
	if (result < 0)
		T_THROW_EXCEPTION("SharedMemory", "Functtion shmctl failed to deallocate shared memory", true, 0xCE00015C,)
	return result;
}
