#include "lab1-2.h"

#include <locale.h>

struct DirWalkOptions flags = { false, false, false, false };

int main(const int argc, TMessage* const argv)
{
	setlocale(LC_COLLATE, "ru_RU");
	const char* directory = DEFAULT_DIRECTORY;

	for (int index = 1; index < argc; ++index)
	{
		if (argv[index][0] == '-')
		{
			if (argv[index][1] == '\0')
			{
				printf(DIR_WALK_WARNING"Token %s is not acceptable.\n", argv[index]);
				return EXIT_FAILURE;
			}
			for (size_t j = 1u; j < T_CLASS(TMessage, size)(argv[index]); ++j) switch (argv[index][j])
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
				printf(DIR_WALK_WARNING"Token %c in %s is not acceptable.\n", argv[index][j], argv[index]);
				return EXIT_FAILURE;
			}
		}
		else if (index == 1)
		{
			TMessage directory_name = argv[index];
			DIR* dr = opendir(directory_name);
			if (dr == nullptr)  // open dir returns NULL if couldn't open directory
			{
				printf(DIR_WALK_WARNING"The directory %s is invalid.\n", directory_name);
				return EXIT_FAILURE;
			}
			directory = directory_name;
			closedir(dr);
		}
		else
		{
			printf(DIR_WALK_WARNING"Token %s is not acceptable.\n", argv[index]);
			return EXIT_FAILURE;
		}
	}
	if (!flags.links && !flags.dirs && !flags.files) flags.links = flags.dirs = flags.files = true;		//	Print all

	if (flags.dirs) printf("%s\n", directory);
	return dir_walk(directory);
}
