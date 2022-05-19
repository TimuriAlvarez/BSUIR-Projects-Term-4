#include <time.h>

#include "ttimer.h"
#include "timport.h"

struct T_CLASS(TTimer, T_ALLOCATOR_POSTFIX)
{
	clock_t start,
			stop;
};

T_IMPORT_MEMORY_DEFINITION(T_CLASS(TTimer, T_ALLOCATOR_POSTFIX))

TTimer T_CLASS(TTimer, default_constructor)(void)
{
	return T_MEMORY_MANAGER(T_CLASS(TTimer, T_ALLOCATOR_POSTFIX), allocate)(1);
}
TTimer T_CLASS(TTimer, constructor)(void)
{
	TTimer timer = T_CLASS(TTimer, default_constructor)();
	T_CLASS(TTimer, start)(timer);
	return timer;
}
TTimer T_CLASS(TTimer, destructor)(TTimer const timer)
{
	return T_MEMORY_MANAGER(T_CLASS(TTimer, T_ALLOCATOR_POSTFIX), deallocate)(timer);
}

void T_CLASS(TTimer, start)(TTimer const timer)
{
	timer->start = clock();
}
void T_CLASS(TTimer, stop)(TTimer const timer)
{
	timer->stop = clock();
}
clock_t T_CLASS(TTimer, duration)(TTimer const timer)
{
	return timer->stop - timer->start;
}

clock_t T_CLASS(TTimer, clocks_per_second)(void)
{
	return CLOCKS_PER_SEC;
}

ldouble T_CLASS(TTimer, miliseconds)(TTimer const timer)
{
	return (ldouble)(T_CLASS(TTimer, duration)(timer)) * 1000.0 / T_CLASS(TTimer, clocks_per_second)();
}
ldouble T_CLASS(TTimer, seconds)(TTimer const timer)
{
	return (ldouble)(T_CLASS(TTimer, duration)(timer)) / T_CLASS(TTimer, clocks_per_second)();
}
