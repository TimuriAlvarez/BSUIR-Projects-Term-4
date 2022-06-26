#include "tdirectory.h"

#include <unistd.h>

#define T_THROW_DIR_FAILED_OPENING T_THROW_EXCEPTION("TFilesystem::TDir", "Failed to open the directory", terminate, 0xFE00F0, return dir;)
#define T_THROW_DIR_SELF_COPYING T_THROW_EXCEPTION("TFilesystem::TDir", "Self-copying is a forbidden behaviour", terminate, 0xFE00F5, )
#define T_THROW_DIR_FAILED_CLOSING T_THROW_EXCEPTION("TFilesystem::TDir", "Failed to close the directory", terminate, 0xFE00F9, )
#define T_THROW_DIR_FAILED_REMOVING T_THROW_EXCEPTION("TFilesystem::TDir", "Failed to create the directory", terminate, 0xFE00FD, return; )
#define T_THROW_DIR_FAILED_CREATING T_THROW_EXCEPTION("TFilesystem::TDir", "Failed to create the directory", terminate, 0xFE00FC, return; )
#define T_THROW_DIR_EXISTANCE_EXPECTED(E_RETURN) T_THROW_EXCEPTION("TFilesystem::TDir", "Directory does not exist which was unexpected", terminate, 0xFE00FE, return E_RETURN;)
#define T_THROW_DIR_EXISTANCE_UNEXPECTED(E_RETURN) T_THROW_EXCEPTION("TFilesystem::TDir", "Directory does exist which was not expected", terminate, 0xFE00FE, return E_RETURN;)

TDir T_CLASS(TDir, close)(TDir const dir, const TBool terminate)
{
	if (dir != nullptr)
		if (closedir(dir)) T_THROW_DIR_FAILED_CLOSING
	return nullptr;
}
/*TBool T_CLASS(TDir, exists)(TMessage dir_path)*/
TDir T_CLASS(TDir, open)(TMessage dir_path, const TBool terminate)
{
	if (dir_path == nullptr) return nullptr;
	if (!T_CLASS(TDir, exists)(dir_path)) T_THROW_DIR_EXISTANCE_EXPECTED(nullptr)
	TDir const dir = opendir(dir_path);
	if (dir == nullptr) T_THROW_DIR_FAILED_OPENING
	return dir;
}
void T_CLASS(TDir, create)(TMessage dir_path, const mode_t dir_mode, const TBool terminate)
{
	if (dir_path == nullptr) return;
	if (T_CLASS(TDir, exists)(dir_path)) T_THROW_DIR_EXISTANCE_UNEXPECTED()
	if (mkdir(dir_path, dir_mode)) T_THROW_DIR_FAILED_CREATING
}
void T_CLASS(TDir, remove)(TMessage dir_path, const TBool terminate)
{
	if (dir_path == nullptr) return;
	if (!T_CLASS(TDir, exists)(dir_path)) T_THROW_DIR_EXISTANCE_EXPECTED()
	T_CLASS(TDir, erase)(dir_path, true);
	rmdir(dir_path);
}

void T_CLASS(TDir, erase_helper)(const TFilesystemStats* const entity)
{
	if (entity->type == kFSTypeDirectory) T_CLASS(TDir, remove)(entity->path, true);
	else T_CLASS(TFile, remove)(entity->path, true);
}
void T_CLASS(TDir, erase)(TMessage dir_path, const TBool terminate)
{
	if (!T_CLASS(TDir, exists)(dir_path)) T_THROW_DIR_EXISTANCE_EXPECTED()
	TDirContent content = T_CLASS(TDirContent, constructor)(dir_path);
	T_CLASS(TDirContent, dirwalk)(content, true, T_CLASS(TDir, erase_helper), false);
	T_CLASS(TDirContent, destructor)(content);
}
void T_CLASS(TDir, touch)(TMessage dir_path, const mode_t dir_mode)
{
	if (!T_CLASS(TDir, exists)(dir_path))
		T_CLASS(TDir, create)(dir_path, dir_mode, true);
}
void T_CLASS(TDir, untouch)(TMessage dir_path)
{
	if (T_CLASS(TDir, exists)(dir_path))
		T_CLASS(TDir, remove)(dir_path, true);
}
