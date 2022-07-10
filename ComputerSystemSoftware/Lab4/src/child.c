#include "tlib.h"

#define CYCLE 10

extern SharedMemoryID memory_id;

struct
{
	size_t iteration;
	TBool is_allowed_printing;
	size_t zz, zo, oz, oo;
} ChildStats;
struct
{
	int a, b;
} ChildData;
void signal_handler(const int signal)
{
	switch(signal)
	{
	case SIGALRM:
		if (ChildData.a ==0)
		{
			if (ChildData.b ==0) ++ChildStats.zz;
			else ++ChildStats.zo;
		}
		else
		{
			if (ChildData.b ==0) ++ChildStats.oz;
			else ++ChildStats.oo;
		}
		alarm(1);
		++ChildStats.iteration;
		if (ChildStats.iteration % CYCLE == 0)
		{
			T_CLASS(SharedMemory, write)(memory_id, getpid());
			kill(getppid(), SIGUSR1);
		}
		return;
	case SIGUSR1:
		switch (T_CLASS(SharedMemory, read)(memory_id))
		{
		case SHMEM_MUTE_PROCESS:
			ChildStats.is_allowed_printing = false;
			return;
		case SHMEM_UNMUTE_PROCESS:
			ChildStats.is_allowed_printing = true;
			return;
		case SHMEM_PRINT_PROCESS:
			if (ChildStats.is_allowed_printing == false) return;
			T_CLASS(TConsole, print)(kLog, "ppid: %d; pid: %d; ", getppid(), getpid());
			T_CLASS(TConsole, print)(kLog, "'00': %zu\t\t'01': %zu\t\t", ChildStats.zz, ChildStats.zo);
			T_CLASS(TConsole, print)(kLog, "'10': %zu\t\t'11': %zu.\n", ChildStats.oz, ChildStats.oo);
			return;
		default:
			return;
		}
	default:
		return;
	}
}

void child_function(void)
{
	struct sigaction sigaction_handler;
	sigaction_handler.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sigaction_handler, nullptr);
	sigaction(SIGUSR2, &sigaction_handler, nullptr);
	sigaction(SIGALRM, &sigaction_handler, nullptr);

	ChildStats.iteration = 0u;
	ChildStats.is_allowed_printing = false;
	ChildStats.zz = ChildStats.zo = ChildStats.oz = ChildStats.oo = 0u;
	ChildData.a = ChildData.b = 0;
	alarm(1);

	while (true)
	{
		sleep(0);
		ChildData.a = 1;
		sleep(0);
		ChildData.b = 1;
		sleep(0);
		ChildData.a = 0;
		sleep(0);
		ChildData.b = 0;
	}
}
