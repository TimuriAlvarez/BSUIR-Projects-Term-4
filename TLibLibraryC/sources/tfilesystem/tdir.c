#pragma once

//#include <sys/stat.h>

#include "../tfilesystem.h"

TFlag T_CLASS(TDir, exists)(TMessage dir_path)
{
	if (dir_path == nullptr) return false;
	if (T_CLASS(TFile, exists)(dir_path)) return false;
	TFile const dir = fopen(dir_path, "r");
	const TFlag result = dir == nullptr ? false : true;
	T_CLASS(TFile, close)(dir, false);
	return result;
}
