#include "../../TLibLibraryC/tlib.c"

TString parce_path(TMessage path);

void T_CLASS(TFilesystem, FileCopy)(TMessage from_path, TMessage to_path)
{
	T_CLASS(TConsole, print)(kDebug, "FileCopy: from %s to %s", from_path, to_path);
	if (from_path == nullptr || to_path == nullptr) return;
	T_CLASS(TFile, copy)(from_path, to_path, true);

	struct stat st;
	stat(from_path, &st);
	chmod(to_path, st.st_mode);
	chown(to_path, st.st_uid, st.st_gid);
}
void T_CLASS(TFilesystem, DirCopy)(TMessage from_path, TMessage to_path);
void T_CLASS(TFilesystem, DirCopyHelper)(const TFilesystemStats* const entity)
{
	if (entity->type == kFSTypeDirectory) T_CLASS(TFilesystem, DirCopy)(entity->path, entity->reserved);
	else T_CLASS(TFilesystem, FileCopy)(entity->path, entity->reserved);
}
void T_CLASS(TFilesystem, DirCopy)(TMessage from_path, TMessage to_path)
{
	T_CLASS(TConsole, print)(kDebug, "DirCopy : from %s to %s", from_path, to_path);
	if (from_path == nullptr || to_path == nullptr) return;
	T_CLASS(TDir, create)(to_path, 0777, true);

	TDirContent content = T_CLASS(TDirContent, constructor)(from_path);
	FOR_EACH_ITERATOR_FROM(entity, TVector, TFilesystemStats, content)
	{
		TString temp = parce_path(entity->path);
		entity->reserved = T_CLASS(TString, constructor)("%s/%s", to_path, temp);
		T_CLASS(TString, destructor)(temp);
	}
	T_CLASS(TDirContent, dirwalk)(content, true, T_CLASS(TFilesystem, DirCopyHelper), true);
	T_CLASS(TDirContent, destructor)(content);

	struct stat st;
	stat(from_path, &st);
	chmod(to_path, st.st_mode);
	chown(to_path, st.st_uid, st.st_gid);
}

void T_CLASS(TFilesystem, FSObjectCopy)(TMessage from_path, TMessage to_path)
{
	if (T_CLASS(TDir, isDir)(from_path)) T_CLASS(TFilesystem, DirCopy)(from_path, to_path);
	else T_CLASS(TFilesystem, FileCopy)(from_path, to_path);
}
void T_CLASS(TFilesystem, FSObjectMove)(TMessage from_path, TMessage to_path)
{
	if (T_CLASS(TDir, isDir)(from_path)) T_CLASS(TDir, untouch)(to_path);
	else T_CLASS(TFile, untouch)(to_path, true);
	if (T_CLASS(TDir, isDir)(from_path)) T_CLASS(TFilesystem, DirCopy)(from_path, to_path);
	else T_CLASS(TFilesystem, FileCopy)(from_path, to_path);
}
