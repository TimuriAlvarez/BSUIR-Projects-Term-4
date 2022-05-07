#pragma once

#include  <pthread.h>

#include "../../../TLibLibraryC/tlib.h"

#define CONTAINER_DATA_TYPE pthread_t
#include "../../../TContainersC/timport/tvector.h"
#define CONTAINER_DATA_TYPE uint
#include "../../../TContainersC/timport/tvector.h"

TBool vector_is_empty(T_CONTAINER(TVector, pthread_t, Container) const container);
void print_hint(void);
void top_bar(T_CONTAINER(TVector, pthread_t, Container) const container);

typedef enum
{
	kNoAction,
	kMuteThread,
	kUnmuteThread,
	kPrintThread,
	kKillThread,
	kGatherStats,
} ThreadAction;
