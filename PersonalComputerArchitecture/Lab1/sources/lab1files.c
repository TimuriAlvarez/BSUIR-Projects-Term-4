#include "tlib.h"

void writing_mode(void* const parameters)
{
	if (parameters != nullptr) return;
	const int port = port_open(0u);
	while (true)
	{
		TString const str = T_CLASS(TConsole, getline)("any string to port", true);
		if (T_CLASS(TString, empty)(str)) break;
		port_write(port, str);
		T_CLASS(TString, destructor)(str);
	}
	port_close(port);
}
void reading_mode(void* const parameters)
{
	if (parameters != nullptr) return;
	const int port = port_open(1u);
	while (true)
	{
		T_CLASS(TConsole, echo)(false);
		TString const str = port_read(port);
		T_CLASS(TConsole, echo)(true);
		T_CLASS(TConsole, print)(kOutput, "Data from the port:\n");
		T_CLASS(TConsole, print)(kLog, "\t%s", str);
		T_CLASS(TConsole, print)(kOutput, "\n");
		if (T_CLASS(TConsole, confirmation)("stop reading the port") == true) break;
		T_CLASS(TString, destructor)(str);
	}
	port_close(port);
}
