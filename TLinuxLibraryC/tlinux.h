#pragma once

#include "../TLibLibraryC/tlib.h"

void T_CLASS(TLinux, constructor)(void);
void T_CLASS(TLinux, destructor)(void);

#ifdef __linux__
#include "sources/tfilesystem.h"
#else
#include "sources/tinterface.h"
#endif
