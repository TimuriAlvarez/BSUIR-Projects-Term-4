#include "tlib.h"

int main(void)
{
	TConsole__default_constructor();

	TConsole__print(kInput, "kInput\n");
	TConsole__print(kOutput, "kOutput\n");
	TConsole__print(kError, "kError\n");
	TConsole__print(kLog, "kLog\n");
	TConsole__print(kDebug, "kDebug\n");

	return 0;
}
