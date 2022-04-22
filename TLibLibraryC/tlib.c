#include "tlib.h"

#include "sources/tbasic.c"
#include "sources/tstring.c"
#include "sources/tfilesystem.c"
#include "sources/tconio.c"
#include "sources/ttimer.c"

void T_CLASS(TLib, constructor)(void)
{
	T_CLASS(TConsole, default_constructor)();
}
void T_CLASS(TLib, destructor)(void)
{
	T_CLASS(TConsole, destructor)();
}
