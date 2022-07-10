#include <time.h>

#include "tlib.h"

#define T_THROW_TOKEN T_THROW_EXCEPTION("DestroyDrive", "Unknown token", true, 0xCE000101,)

TString parce_path(TMessage path);
void T_CLASS(TFilesystem, FSObjectCopy)(TMessage from_path, TMessage to_path);
void T_CLASS(TFilesystem, FSObjectMove)(TMessage from_path, TMessage to_path);

void T_CLASS(Destdrive, help)(void)
{
	T_CLASS(TConsole, print)(kOutput, "Valid commands are:\n"
									  "\thelp\t - see this message\n"
									  "\tlist\t - display all available backups\n"
									  "\tbackup\t - create backup copy of 'source'\n"
									  "\trestore\t - restore data from 'copy' \n"
									  "\n"
									  "\tunlock\t - force application unlock\n");
}
void print_backup(const TFilesystemStats* const entity)
{
	if (entity->type != kFSTypeDirectory) return;
	TString temp = T_CLASS(TString, substring)(entity->path, 5, T_CLASS(TString, size)(entity->path));
	if (/*temp == nullptr || */T_CLASS(TString, equal)(temp, ".") || T_CLASS(TString, equal)(temp, "..")/* || T_CLASS(TString, equal)(temp, ".lock")*/)
		T_RETURN_VOID(T_CLASS(TString, destructor)(temp);)
	T_CLASS(TConsole, print)(kOutput, "'%s' -> ", temp);
	T_CLASS(TString, destructor)(temp);
	temp = T_CLASS(TString, constructor)("%s/location", entity->path);
	TFile file = T_CLASS(TFile, open)(temp, "r", true);
	TString source_path = T_CLASS(TConsole, getfile)(file, nullptr, false);
	T_CLASS(TFile, close)(file, true);
	T_CLASS(TConsole, print)(kOutput, "'%s'\n", source_path);
	T_CLASS(TString, destructor)(temp);
	T_CLASS(TString, destructor)(source_path);
}
void T_CLASS(Destdrive, list)(void)
{
	//T_CLASS(syscall, execute)("ls -1 data");
	TDirContent content = T_CLASS(TDirContent, constructor)("data");
	T_CLASS(TDirContent, dirwalk)(content, false, print_backup, true);
	T_CLASS(TDirContent, destructor)(content);
}
void T_CLASS(Destdrive, backup)(TMessage source_path)
{
	if (!(T_CLASS(TFile, exists)(source_path) || T_CLASS(TDir, exists)(source_path))) T_THROW_EXCEPTION("DestroyDrive", "Invalid sourse path", true, 0xCE000102, )
	time_t t = time(nullptr);
	struct tm *tm = localtime(&t);
	TString time = T_CLASS(TString, constructor)("%s", asctime(tm));
	time[T_CLASS(TString, size)(time) - 1] = '\0';
	FOR_EACH_ITERATOR_FROM(character, TString, char, time)
			if (*character == ':') *character = '-';
	TString backup_path = T_CLASS(TString, constructor)("data/%s", time);
	TString backup_location = T_CLASS(TString, constructor)("%s/location", backup_path);
	T_CLASS(TDir, create)(backup_path, 0777, true);
	T_CLASS(TFile, create)(backup_location, true);
	TFile file = T_CLASS(TFile, open)(backup_location, "w", true);
	fprintf(file, "%s", source_path);
	T_CLASS(TFile, close)(file, true);
	T_CLASS(TFilesystem, FSObjectCopy)(source_path, T_CLASS(TString, constructor)("%s/%s", backup_path, parce_path(source_path)));
	T_CLASS(TString, destructor)(backup_path);
	T_CLASS(TString, destructor)(backup_location);
	T_CLASS(Destdrive, list)();
}
void T_CLASS(Destdrive, restore)(TMessage date_and_time)
{
	T_CLASS(Destdrive, list)();
	TString backup = T_CLASS(TString, constructor)("data/%s", date_and_time);
	if (!T_CLASS(TDir, exists)(backup))
		T_THROW_EXCEPTION("DestroyDrive", "Invalid backup path", true, 0xCE000102, )
	TString backup_location = T_CLASS(TString, constructor)("%s/location", backup);
	TFile file = T_CLASS(TFile, open)(backup_location, "r", true);
	TString source_path = T_CLASS(TConsole, getfile)(file, nullptr, false);
	T_CLASS(TFile, close)(file, true);
	TString backup_path = T_CLASS(TString, constructor)("%s/%s", backup, parce_path(source_path));
	T_CLASS(TFilesystem, FSObjectMove)(backup_path, source_path);
	T_CLASS(TString, destructor)(backup);
	T_CLASS(TString, destructor)(backup_path);
	T_CLASS(TString, destructor)(backup_location);
	T_CLASS(TString, destructor)(source_path);
}

void T_CLASS(Destdrive, unlock)(void)
{
	T_CLASS(TFile, untouch)("data/.lock", false);
}

void T_CLASS(Destdrive, lock)(void)
{
	if (T_CLASS(TFile, exists)("data/.lock"))
		T_THROW_EXCEPTION("Destroy Drive", "Application is locked", true, 0xCE0001, T_RETURN_VOID(T_CLASS(TConsole, print)(kOutput, "Application is already running!\n");));
	T_CLASS(TFile, touch)("data/.lock");
	T_CLASS(syscall, atexit)(T_CLASS(Destdrive, unlock));
}

int main(int argc, TMessage* const argv)
{
	T_CLASS(TConsole, debug)(true);
	T_CLASS(TConsole, library)(false);
	switch(argc)
	{
	case 1:
		T_CLASS(Destdrive, help)();
		return 0;
	case 2:
		if (T_CLASS(TString, equal)(argv[1], "list")) T_CLASS(Destdrive, list)();
		elif (T_CLASS(TString, equal)(argv[1], "unlock")) T_CLASS(Destdrive, unlock)();
		else T_CLASS(Destdrive, help)();
		return 0;
	case 3:
		T_CLASS(Destdrive, lock)();
		if (T_CLASS(TString, equal)(argv[1], "backup")) T_CLASS(Destdrive, backup)(argv[2]);
		elif (T_CLASS(TString, equal)(argv[1], "restore")) T_CLASS(Destdrive, restore)(argv[2]);
		else T_CLASS(Destdrive, help)();
		return 0;
	default:
		return -1;
	}
}
