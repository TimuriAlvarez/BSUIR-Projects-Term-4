#pragma once

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>

#include "../../../TLibLibraryC/tlib.h"

#define CONTAINER_DATA_TYPE pid_t
#include "../../../TContainersC/timport/tvector.h"

#include "memory.h"
