#pragma once

#include "tlib.h"

#define DIR_TYPE 4
#define FILE_TYPE 8
#define LINK_TYPE 10

struct DirWalkOptions
{
	TBool links;
	TBool dirs;
	TBool files;
	TBool sort;
};

int dir_walk(TMessage directory);
