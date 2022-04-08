#include "tlib.h"

int main(void)
{
	TConsole__default_constructor();

	TConsole__print(kInput, "kInput\n");
	TConsole__print(kOutput, "kOutput\n");
	TConsole__print(kError, "kError\n");
	TConsole__print(kLog, "kLog\n");
	TConsole__print(kDebug, "kDebug0\n");

	TConsole__debug(true);
	TConsole__print(kDebug, "kDebug1\n");

	TConsole__debug(false);
	TConsole__print(kDebug, "kDebug2\n");

	return 0;
}
