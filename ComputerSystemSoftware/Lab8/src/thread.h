#pragma once
#include "tlib.h"

typedef pthread_t thread;

#define CONTAINER_DATA_TYPE thread
#include "../../../TContainersC/timport/tvector.h"

void add_producer(void);
void add_taker(void);
void kill_producer(void);
void kill_taker(void);
void destroy_producers(void);
void destroy_takers(void);
