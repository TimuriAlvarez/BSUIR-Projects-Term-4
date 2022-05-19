#pragma once

#include <pthread.h>

#include "tlib.h"

typedef pthread_t TThread;

#define CONTAINER_DATA_TYPE TThread
#include "../../../TContainersC/timport/tvector.h"
