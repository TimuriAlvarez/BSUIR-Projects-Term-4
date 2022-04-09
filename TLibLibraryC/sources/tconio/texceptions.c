#include "../tconio.h"

void handle_exception(const TException exception)
{
	T_CLASS(TConsole, print)(kError, "An exception was thrown: %s Exception.\n", exception.type == nullptr ? "Unknown" : exception.type);
	T_CLASS(TConsole, print)(kError, "\t\t\t%s.\n", exception.description == nullptr ? "No description available" : exception.description);
	T_CLASS(TConsole, print)(kError, "The exception was thrown by:\n");
	T_CLASS(TConsole, print)(kError, "\t\t\tFile:\t\t%s,\n", exception.code_location.file);
	T_CLASS(TConsole, print)(kError, "\t\t\tLine:\t\t%zu,\n", exception.code_location.line);
	T_CLASS(TConsole, print)(kError, "\t\t\tFunction:\t%s.\n", exception.code_location.function);
	T_CLASS(TConsole, print)(kError, "Exception status:\t%s critical.\n", exception.terminate ? "Is" : "Isn't");
	T_CLASS(TConsole, print)(kError, "The exception code:\t%d\t(0x%X).\n\n", exception.code, exception.code);
	if (exception.terminate)
	{
		T_CLASS(TConsole, print)(kError, "Execution was terminated due to catching the critical exception.\n\n");
		T_CLASS(TConsole, print)(kError, "[process exited with code %d (0x%X)]\n\n", exception.code, exception.code);
		exit(exception.code);
	}
}
