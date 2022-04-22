#pragma once

#include "tbasic.h"

typedef struct T_CLASS(TTimer, T_ALLOCATOR_POSTFIX) T_CLASS(TTimer, T_ALLOCATOR_POSTFIX);
typedef T_CLASS(TTimer, T_ALLOCATOR_POSTFIX)* TTimer;

TTimer T_CLASS(TTimer, default_constructor)(void);
TTimer T_CLASS(TTimer, constructor)(void);
TTimer T_CLASS(TTimer, destructor)(TTimer const timer);

void T_CLASS(TTimer, start)(TTimer const timer);
void T_CLASS(TTimer, stop)(TTimer const timer);

ldouble T_CLASS(TTimer, miliseconds)(TTimer const timer);
ldouble T_CLASS(TTimer, seconds)(TTimer const timer);
