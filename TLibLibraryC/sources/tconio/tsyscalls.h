#pragma once

#include "../tconio.h"

void T_FUNCTION(syscall, execute)(TMessage command);

void T_FUNCTION(syscall, pause)(void);
void T_FUNCTION(syscall, clear)(void);
void T_FUNCTION(syscall, update)(void);
int T_FUNCTION(syscall, atexit)(void(*function)(void));

void T_FUNCTION(syscall, exit)(const int);
