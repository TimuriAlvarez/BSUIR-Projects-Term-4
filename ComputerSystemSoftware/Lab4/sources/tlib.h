#pragma once

#ifdef __linux__
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#endif

#include "../../../TLibLibraryC/tlib.h"
#include "../../../TLinuxInterfaceC/tlinux.h"

#define CONTAINER_DATA_TYPE pid_t
#include "../../../TContainersC/timport/tvector.h"

#include <errno.h>
#include <signal.h>
#include "memory.h"
