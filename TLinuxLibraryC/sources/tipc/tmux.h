#pragma once

#include "../tipc.h"

typedef pthread_mutex_t* TMutex;

TMutex T_CLASS(TMutex, default_constructor)(void);
TMutex T_CLASS(TMutex, constructor)(void);
TMutex T_CLASS(TMutex, destructor)(TMutex mutex);

void T_CLASS(TMutex, lock)(TMutex mutex);
void T_CLASS(TMutex, unlock)(TMutex mutex);
