#include "tlib.h"

int menu_help(void);
void menu_list(void);
void menu_generate(void);
void menu_clear(void);
void menu_process(TMessage file_name);

llint quantity = 0;

int main(int argc, TMessage* const argv)
{
	switch (argc)
	{
	case 1:
		return menu_help();
	case 2:
		if (T_CLASS(TString, equal)(argv[1], "/l")) menu_list();
		elif (T_CLASS(TString, equal)(argv[1], "/g")) menu_generate();
		elif (T_CLASS(TString, equal)(argv[1], "/c")) menu_clear();
		elif (T_CLASS(TString, equal)(argv[1], "/h")) menu_help();
		else
		{
			/* while (true)
			 * {
			 *	T_CLASS(TConsole, print)(kOutput, "Enter the quantity of threads: ");
			 * 	T_CLASS(TConsole, scan)("%lld", &quantity);
			 * 	if (quantity > 0) break;
			 * 	T_CLASS(TConsole, print)(kError, "Invalid  value!\n");
			 * }*/
			quantity = 10;
			menu_process(argv[1]);
			/* TString command = T_CLASS(TString, constructor)("less temp/%s", argv[1]);
			 * T_FUNCTION(syscall, execute)(command);
			 * T_CLASS(TString, destructor)(command);
			 * */
		}
		return 0;
	default:
		T_THROW_EXCEPTION("Main", "invalid quantity of input parameters", true, 0xCE000100,)
	}
}
