#pragma once

#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <semaphore.h>

#include "../tlinux.h"

typedef int TSharedMemory;
#define T_IPC_SHM(T_IPC_TYPE, T_METHOD) T_CONTAINER(TSharedMemory, T_IPC_TYPE, T_METHOD)

#define T_IPC_MODE 0666

#include "tipc/tshm.h"
#include "tipc/tsem.h"
#include "tipc/tmux.h"
