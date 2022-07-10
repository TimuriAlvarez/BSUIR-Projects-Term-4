#pragma once
#include "tlib.h"

typedef struct
{
	TString message;
	ullint checksum;
	uint added;
	uint deleted;
} Circle;

#define CONTAINER_DATA_TYPE Circle
#include "../../../TContainersC/timport/tlist.h"

void append_circle(void);
void print_circle(void);
void free_circle(void);

void produce_message(T_CONTAINER(TList, Circle, T_ITERATOR_POSTFIX) const iterator);
void take_message(T_CONTAINER(TList, Circle, T_ITERATOR_POSTFIX) const iterator);
