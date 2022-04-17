#include "memory.h"

#include <errno.h>
#include <stdio.h>

#define T_LENGTH sizeof(int)

SharedMemory T_CLASS(SharedMemory, constructor)(void)
{
	SharedMemory map = mmap(nullptr, T_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_PRIVATE, 0, 0);
	if (map == MAP_FAILED) perror("Error mapping the file");
	return map;
}

void T_CLASS(SharedMemory, write)(SharedMemory memory, int value)
{
	printf("1\n");
	memory[0] = value;
}

int T_CLASS(SharedMemory, read)(SharedMemory memory)
{
	printf("2\n");
	return memory[0];
}

SharedMemory T_CLASS(SharedMemory, destructor)(SharedMemory memory)
{
	munmap(memory, T_LENGTH);
	return nullptr;
}
