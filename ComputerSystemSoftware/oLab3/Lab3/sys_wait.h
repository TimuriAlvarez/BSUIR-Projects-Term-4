#pragma once

#include "sys_types.h"

pid_t  wait(int*);
int    waitid(idtype_t, id_t, siginfo_t*, int);
pid_t  waitpid(pid_t, int*, int);

#define WEXITSTATUS(PROCESS) PROCESS

#define WNOHANG 1
