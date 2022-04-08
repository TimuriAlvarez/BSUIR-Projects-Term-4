#pragma once

#ifdef _WIN32
#include "../../../TLibLibraryC/include/tlinux.h"
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
#include <signal.h>

#include "../../../TLibLibraryC/tlib.h"
