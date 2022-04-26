#pragma once

#include "sources/tbasic.h"
#include "sources/timport.h"
#include "sources/tstring.h"
#include "sources/tfilesystem.h"
#include "sources/tconio.h"
#include "sources/ttimer.h"

#undef NULL

void T_CLASS(TLib, constructor)(void) __attribute__((constructor));
void T_CLASS(TLib, destructor)(void) __attribute__((destructor));

#include "../TLinuxLibraryC/tlinux.h"
