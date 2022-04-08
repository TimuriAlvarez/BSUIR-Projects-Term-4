#pragma once

#include "../../../TLibLibraryC/tlib.h"
#include "../../../TLinuxInterfaceC/tlinux.h"

#ifdef __linux__
#include <dirent.h>
#endif

#define DIR_TYPE 4
#define FILE_TYPE 8
#define LINK_TYPE 10

#define DEFAULT_DIRECTORY "."
#define DIR_WALK_WARNING "DIR_WALK_WARNING: "

struct DirWalkOptions
{
	TFlag links;
	TFlag dirs;
	TFlag files;
	TFlag sort;
};
