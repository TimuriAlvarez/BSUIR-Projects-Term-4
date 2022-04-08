#pragma once

#include "../../../Tlib Library C/Tlib Library C/tlib.h"

#ifdef _WIN32
#include "../../../Tlib Library C/Tlib Library C/tlinux/sys/types.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/sys/wait.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/unistd.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/signal.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/time.h"
#include <signal.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#endif
