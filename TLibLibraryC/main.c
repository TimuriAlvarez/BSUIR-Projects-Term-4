#include "tlib.h"

int main(void)
{
	T_CLASS(TConsole, debug)(true);
	T_CLASS(TConsole, library)(true);
	TString temp = T_CLASS(TString, constructor)(nullptr);
	T_CLASS(TConsole, print)(kLibrary, "%s", temp); T_CLASS(TString, destructor)(temp);
	temp = T_CLASS(TString, constructor)("%c", 'a');
	T_CLASS(TConsole, print)(kLibrary, "%s", temp); T_CLASS(TString, destructor)(temp);
	temp = T_CLASS(TString, constructor)("%s + %s", nullptr, "ABCD");
	T_CLASS(TConsole, print)(kLibrary, "%s", temp); T_CLASS(TString, destructor)(temp);
	temp = T_CLASS(TString, constructor)("%p", (void*)0xFF);
	T_CLASS(TConsole, print)(kLibrary, "%s", temp); T_CLASS(TString, destructor)(temp);
	return 0;
}
