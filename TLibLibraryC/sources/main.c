#include "tlib.h"

int main(void)
{
	T_CLASS(TConsole, debug)(true);
	T_CLASS(TConsole, library)(true);

	T_CONTAINER(TString, char, T_CONTAINER_POSTFIX) string = T_CLASS(TString, constructor)("%% 1 %% 2 %% 3 %% %%");
	int one, two, three;
	T_CLASS(TConsole, print)(kLog, "%s\n", string);
	T_CLASS(TString, parser)(string, "%% %d %% %d %% %d %% %%", &one, &two, &three);
	T_CLASS(TConsole, print)(kLog, "%d\n%d\n%d\n", one, two, three);
	T_CLASS(TString, destructor)(string);

	return 0;
}
