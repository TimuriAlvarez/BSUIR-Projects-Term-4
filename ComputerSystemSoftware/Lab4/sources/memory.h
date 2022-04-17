#pragma once

#include "tlib.h"

typedef int* SharedMemory;

SharedMemory T_CLASS(SharedMemory, constructor)(void);
void T_CLASS(SharedMemory, write)(SharedMemory memory, int value);
int T_CLASS(SharedMemory, read)(SharedMemory memory);
SharedMemory T_CLASS(SharedMemory, destructor)(SharedMemory memory);

#define SHMEM_MUTE_PROCESS		-1
#define SHMEM_UNMUTE_PROCESS	-2
#define SHMEM_PRINT_PROCESS		-3
