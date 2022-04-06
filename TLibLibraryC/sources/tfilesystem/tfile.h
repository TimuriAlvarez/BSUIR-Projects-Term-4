#pragma once

#include "../tbasic.h"

/*	Hint:
 *	"r"		Opens a file for reading. The file must exist.
 *	"w"		Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
 *	"a"		Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
 *	"r+"	Opens a file to update both reading and writing. The file must exist.
 *	"w+"	Creates an empty file for both reading and writing.
 *	"a+"	Opens a file for reading and appending.
 */

TFile T_CLASS(TFile, close)(TFile const file, const TFlag terminate);
TFlag T_CLASS(TFile, exists)(TMessage file_path);
TFile T_CLASS(TFile, open)(TMessage file_path, TMessage file_mode, const TFlag terminate);
void T_CLASS(TFile, create)(TMessage file_path, const TFlag terminate);
void T_CLASS(TFile, remove)(TMessage file_path, const TFlag terminate);
void T_CLASS(TFile, erase)(TMessage file_path, const TFlag terminate);
void T_CLASS(TFile, touch)(TMessage file_path);
void T_CLASS(TFile, copy)(TMessage old_file_path, TMessage new_file_path, const TFlag terminate);
void T_CLASS(TFile, move)(TMessage old_file_path, TMessage new_file_path, const TFlag terminate);
