#pragma once

#include "../tbasic.h"

void T_FUNCTION(syscall, pause)(void);
void T_FUNCTION(syscall, clear)(void);
void T_FUNCTION(syscall, update)(void);
int T_FUNCTION(syscall, atexit)(void(*function)(void));
