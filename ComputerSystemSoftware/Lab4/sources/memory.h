#pragma once

#include "tlib.h"

typedef int SharedMemoryID;
typedef int* SharedMemory;

SharedMemoryID T_CLASS(SharedMemory, constructor)(void);
void T_CLASS(SharedMemory, write)(SharedMemoryID memory, int value);
int T_CLASS(SharedMemory, read)(SharedMemoryID memory);
SharedMemoryID T_CLASS(SharedMemory, destructor)(SharedMemoryID memory);

#define SHMEM_MUTE_PROCESS		-1
#define SHMEM_UNMUTE_PROCESS	-2
#define SHMEM_PRINT_PROCESS		-3
