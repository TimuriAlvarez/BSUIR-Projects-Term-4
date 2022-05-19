#pragma once

#include "../tipc.h"

typedef struct TSemaphoreAllocator TSemaphoreAllocator;
typedef TSemaphoreAllocator* TSemaphore;

TSemaphore T_CLASS(TSemaphore, constructor)(TMessage name, const uint default_value);
TSemaphore T_CLASS(TSemaphore, default_constructor)(TMessage name);
TSemaphore T_CLASS(TSemaphore, destructor)(TSemaphore semaphore);

TSemaphore T_CLASS(TSemaphore, open)(TMessage name);
TSemaphore T_CLASS(TSemaphore, close)(TSemaphore semaphore);

uint T_CLASS(TSemaphore, get_value)(TSemaphore semaphore);
void T_CLASS(TSemaphore, increment)(TSemaphore semaphore);
void T_CLASS(TSemaphore, decrement)(TSemaphore semaphore);
void T_CLASS(TSemaphore, set_value)(TSemaphore semaphore, const uint value);
