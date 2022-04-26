#include "tlinux.h"

#ifndef  __linux__
void T_CLASS(TLinux, constructor)(void) {};
void T_CLASS(TLinux, destructor)(void) {};
#else
void T_CLASS(TLinux, constructor)(void) {};
void T_CLASS(TLinux, destructor)(void) {};
#include "sources/tfilesystem.c"
#endif
