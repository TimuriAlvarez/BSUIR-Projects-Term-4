#include "tlib.h"

int main(void)
{
	TConsole__constructor(nullptr, nullptr, nullptr, nullptr);
	TConsole__set_format(kInput, kNormal, true, kYellow);
	TConsole__set_format(kOutput, kNormal, true, kGreen);
	TConsole__set_format(kError, kNormal, true, kRed);
	TConsole__set_format(kLog, kNormal, true, kCyan);
	TConsole__set_format(kDebug, kNormal, true, kPurple);

	TConsole__print(kInput, "kInput\n");
	TConsole__print(kOutput, "kOutput\n");
	TConsole__print(kError, "kError\n");
	TConsole__print(kLog, "kLog\n");
	TConsole__print(kDebug, "kDebug\n");

	return 0;
}
