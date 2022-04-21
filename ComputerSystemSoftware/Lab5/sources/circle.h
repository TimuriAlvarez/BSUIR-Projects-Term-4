#pragma once
#include "tlib.h"

#include <sys/types.h>
#ifdef __linux__
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

struct Circle{
	char message[255];
	unsigned long long checksum;
	unsigned int added;
	unsigned int deleted;
	key_t key;
	int left_shmid;
	int right_shmid;
	int current_shmid;
};

void AppendCircle(struct Circle **to_append);
