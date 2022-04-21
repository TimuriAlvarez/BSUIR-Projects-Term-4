#include "tlib.h"

int main(void)
{
	T_CLASS(TConsole, default_constructor)();
	TString arr[] = {T_CLASS(TConsole, sprint)("%d %d", 123, 123.5),
							T_CLASS(TConsole, sprint)("%c %d -- %f", 'A', 'A', -123.5),
							T_CLASS(TConsole, sprint)("\t\nQWERTYUIO %X", 0xFF)};
	T_CLASS(TConsole, print)(kOutput, "[%s][%s][%s]", arr[0], arr[1], arr[2]);
	T_CLASS(TString, destructor)(arr[0]);
	T_CLASS(TString, destructor)(arr[1]);
	T_CLASS(TString, destructor)(arr[2]);
	return 0;
}
