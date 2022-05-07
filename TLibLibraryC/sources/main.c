#include "tlib.h"

int main(void)
{
	T_CLASS(TConsole, debug)(true);
	T_CLASS(TConsole, library)(true);

	int i = 556, i2;
	float f = -658.545, f2;
	char c = 'b', c2;

	TString string = T_CLASS(TString, constructor)("%d fu %f aa aa aa %c d", i, f, c);
	T_CLASS(TConsole, print)(kLog, "%s\n", string);

	T_CLASS(TString, parser)(string, "%d fu %f aa aa aa %c d", &i2, &f2, &c2);

	T_CLASS(TConsole, print)(kOutput, "i: %d\nf: %f\nc: %c\n", i2, f2, c2);

	return 0;
}
