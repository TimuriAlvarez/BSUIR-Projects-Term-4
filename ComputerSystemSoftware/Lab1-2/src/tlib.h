#pragma once

#include "../../../TLibLibraryC/tlib.h"
#include "../../../TLinuxLibraryC/tlinux.h"

#include "dirwalk.h"

#include <dirent.h>

typedef struct dirent* DirEnt_p;

#define CONTAINER_DATA_TYPE DirEnt_p
#include "../../../TContainersC/timport/tlist.h"
