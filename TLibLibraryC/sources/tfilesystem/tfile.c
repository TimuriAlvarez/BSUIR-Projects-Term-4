#pragma once

#include "tfile.h"
#include "../tstring.h"
#include "../tconio.h"

/*	Hint:
 *	"r"		Opens a file for reading. The file must exist.
 *	"w"		Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
 *	"a"		Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
 *	"r+"	Opens a file to update both reading and writing. The file must exist.
 *	"w+"	Creates an empty file for both reading and writing.
 *	"a+"	Opens a file for reading and appending.
 */

#define T_THROW_FAILED_OPENING T_THROW_EXCEPTION("TFilesystem::TFile", "Failed to open the file", terminate, 0xFE00F0, return file;)
#define T_THROW_SELF_COPYING T_THROW_EXCEPTION("TFilesystem::TFile", "Self-copying is a forbidden behaviour", terminate, 0xFE00F5, )
#define T_THROW_FAILED_CLOSING T_THROW_EXCEPTION("TFilesystem::TFile", "Failed to close the file", terminate, 0xFE00F9, )
#define T_THROW_FAILED_REMOVING T_THROW_EXCEPTION("TFilesystem::TFile", "Failed to create the file", terminate, 0xFE00FD, return; )
#define T_THROW_FAILED_CREATING T_THROW_EXCEPTION("TFilesystem::TFile", "Failed to create the file", terminate, 0xFE00FC, return; )
#define T_THROW_EXISTANCE_EXPECTED(E_RETURN) T_THROW_EXCEPTION("TFilesystem::TFile", "Failed does not exist which was unexpected", terminate, 0xFE00FE, return E_RETURN;)
#define T_THROW_EXISTANCE_UNEXPECTED(E_RETURN) T_THROW_EXCEPTION("TFilesystem::TFile", "Failed does exist which was not expected", terminate, 0xFE00FE, return E_RETURN;)

TFile T_CLASS(TFile, close)(TFile const file, const TBool terminate)
{
	if (file != nullptr)
		if (fclose(file)) T_THROW_FAILED_CLOSING
	return nullptr;
}
TBool T_CLASS(TFile, exists)(TMessage file_path)
{
	if (file_path == nullptr) return false;
	TFile const file = fopen(file_path, "r+");
	const TBool result = file == nullptr ? false : true;
	T_CLASS(TFile, close)(file, false);
	return result;
}
TFile T_CLASS(TFile, open)(TMessage file_path, TMessage file_mode, const TBool terminate)
{
	if (file_path == nullptr) return nullptr;
	if (!T_CLASS(TFile, exists)(file_path)) T_THROW_EXISTANCE_EXPECTED(nullptr)
	TFile const file = fopen(file_path, file_mode);
	if (file == nullptr) T_THROW_FAILED_OPENING
	return file;
}

void T_CLASS(TFile, create)(TMessage file_path, const TBool terminate)
{
	if (file_path == nullptr) return;
	if (T_CLASS(TFile, exists)(file_path)) T_THROW_EXISTANCE_UNEXPECTED()
	TFile const file = fopen(file_path, "w");
	if (file == nullptr) T_THROW_FAILED_CREATING
	T_CLASS(TFile, close)(file, false);
}
void T_CLASS(TFile, remove)(TMessage file_path, const TBool terminate)
{
	if (file_path == nullptr) return;
	if (!T_CLASS(TFile, exists)(file_path)) T_THROW_EXISTANCE_EXPECTED()
	if (remove(file_path) != 0) T_THROW_FAILED_REMOVING
}
void T_CLASS(TFile, erase)(TMessage file_path, const TBool terminate)
{
	if (!T_CLASS(TFile, exists)(file_path)) T_THROW_EXISTANCE_EXPECTED()
	T_CLASS(TFile, remove)(file_path, terminate);
	T_CLASS(TFile, create)(file_path, terminate);
}
void T_CLASS(TFile, touch)(TMessage file_path)
{
	if (!T_CLASS(TFile, exists)(file_path))
		T_CLASS(TFile, create)(file_path, true);
}
void T_CLASS(TFile, untouch)(TMessage file_path, const TBool terminate)
{
	if (T_CLASS(TFile, exists)(file_path))
		T_CLASS(TFile, remove)(file_path, terminate);
}
void T_CLASS(TFile, copy)(TMessage old_file_path, TMessage new_file_path, const TBool terminate)
{
	if (T_CLASS(TString, equal)(old_file_path, new_file_path)) T_THROW_SELF_COPYING
	if (!T_CLASS(TFile, exists)(old_file_path)) T_THROW_EXISTANCE_EXPECTED()
	if (T_CLASS(TFile, exists)(new_file_path)) T_THROW_EXISTANCE_UNEXPECTED()
	T_CLASS(TFile, create)(new_file_path, terminate);
	if (!T_CLASS(TFile, exists)(new_file_path)) T_THROW_EXISTANCE_EXPECTED()
	TFile const old_file = T_CLASS(TFile, open)(old_file_path, "rb", true);
	TFile const new_file = T_CLASS(TFile, open)(new_file_path, "wb", true);
	while (true)
	{
		char temp;
		fread(&temp, sizeof(char), 1u, old_file);
		if (feof(old_file)) break;
		fwrite(&temp, sizeof(char), 1u, new_file);
	}
	T_CLASS(TFile, close)(old_file, terminate);
	T_CLASS(TFile, close)(new_file, terminate);
}
void T_CLASS(TFile, move)(TMessage old_file_path, TMessage new_file_path, const TBool terminate)
{
	T_CLASS(TFile, copy)(old_file_path, new_file_path, terminate);
	T_CLASS(TFile, remove)(old_file_path, terminate);
}
