#include <locale.h>

#include "dirwalk.h"

#define DEFAULT_DIRECTORY "."

#define T_THROW_INVALID_DIRECTORY T_THROW_EXCEPTION("Dirwalk", "Invalid start directory", true, 0xCE00D0, return 0xCE00D0;)
#define T_THROW_INACCEPTABLE_TOKEN T_THROW_EXCEPTION("Dirwalk", "Token is not acceptable", true, 0xCE00D1, return 0xCE00D1;)

struct DirWalkOptions flags = { false, false, false, false };

int main(const int argc, TMessage* const argv)
{
	T_FUNCTION(syscall, clear)();
	setlocale(LC_COLLATE, "ru_RU");
	const char* directory = DEFAULT_DIRECTORY;

	for (int index = 1; index < argc; ++index)
	{
		if (argv[index][0] == '-')
		{
			if (argv[index][1] == '\0') T_THROW_INACCEPTABLE_TOKEN
			for (size_t j = 1u; j < T_CLASS(TString, size)(argv[index]); ++j) switch (argv[index][j])
			{
			case 'l':
				flags.links = true;
				break;
			case 'd':
				flags.dirs = true;
				break;
			case 'f':
				flags.files = true;
				break;
			case 's':
				flags.sort = true;
				break;
			default:
				T_THROW_INACCEPTABLE_TOKEN
			}
		}
		else if (index == 1)
		{
			TMessage directory_name = argv[index];
			DIR* dr = opendir(directory_name);
			if (dr == nullptr)  // open dir returns NULL if couldn't open directory
				T_THROW_INVALID_DIRECTORY
			directory = directory_name;
			closedir(dr);
		}
		else T_THROW_INACCEPTABLE_TOKEN
	}

	if (!flags.links && !flags.dirs && !flags.files) flags.links = flags.dirs = flags.files = true;		//	Print all

	if (flags.dirs) T_CLASS(TConsole, print)(kOutput, "%s\n", directory);
	return dir_walk(directory);
}
