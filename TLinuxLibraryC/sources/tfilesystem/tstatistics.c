#include <sys/stat.h>
#include <unistd.h>

#include "../tfilesystem.h"

#define CONTAINER_DATA_TYPE TFilesystemStats
#include "../../../TContainersC/timport/tvector.c"

typedef struct dirent* TDirEntity;

TFilesystemType T_CLASS(TFilesystemStats, type)(const struct stat entity)
{
	mode_t T_TEMP_M = entity.st_mode;
	const struct stat* ptr = &entity;
#ifdef S_ISLNK
	if (S_ISLNK(T_TEMP_M)) return kFSTypeSymbolicLink;
#endif
#ifdef S_ISBLK
	if (S_ISBLK(T_TEMP_M)) return kFSTypeBlockSpecialFile;
#endif
#ifdef S_ISCHR
	if (S_ISCHR(T_TEMP_M)) return kFSTypeCharacterSpecialFile;
#endif
#ifdef S_ISDIR
	if (S_ISDIR(T_TEMP_M)) return kFSTypeDirectory;
#endif
#ifdef S_ISFIFO
	if (S_ISFIFO(T_TEMP_M)) return kFSTypeFIFOFile;
#endif
#ifdef S_ISSOCK
	if (S_ISSOCK(T_TEMP_M)) return kFSTypeDomainSocket;
#endif
#ifdef S_TYPEISMQ
	if (S_TYPEISMQ(ptr)) return kFSTypeIPCMessageQueue;
#endif
#ifdef S_TYPEISSEM
	if (S_TYPEISSEM(ptr)) return kFSTypeIPCSemaphore;
#endif
#ifdef S_TYPEISSHM
	if (S_TYPEISSHM(ptr)) return kFSTypeIPCSharedMemoryObject;
#endif
#ifdef S_TYPEISTMO
	if (S_TYPEISTMO(ptr)) return kFSTypeIPCTypedMemoryObject;
#endif
#ifdef S_ISREG
	if (S_ISREG(T_TEMP_M)) return kFSTypeRegularFile;
#endif
	return kFSTypeUnknown;
}

TFilesystemPermissions T_CLASS(TFilesystemPermissions, default_constructor)(void)
{
	TFilesystemPermissions result = { false, false, false, false, false, false, false, false, false, false, false, false };
	return result;
}

TFilesystemPermissions T_CLASS(TFilesystemPermissions, constructor)(const struct stat entity)
{
	mode_t T_TEMP_M = entity.st_mode;
	TFilesystemPermissions result = T_CLASS(TFilesystemPermissions, default_constructor)();

	if (T_TEMP_M & S_ISUID) result.set_uid = true;
	if (T_TEMP_M & S_ISGID) result.set_gid = true;
#ifdef S_ISVTX
	if (T_TEMP_M & S_ISVTX) result.sticky_bit = true;
#endif

	if (T_TEMP_M & S_IRUSR) result.usr_r = true;
	if (T_TEMP_M & S_IWUSR) result.usr_w = true;
	if (T_TEMP_M & S_IXUSR) result.usr_x = true;

	if (T_TEMP_M & S_IRGRP) result.grp_r = true;
	if (T_TEMP_M & S_IWGRP) result.grp_w = true;
	if (T_TEMP_M & S_IXGRP) result.grp_x = true;

	if (T_TEMP_M & S_IROTH) result.oth_r = true;
	if (T_TEMP_M & S_IWOTH) result.oth_w = true;
	if (T_TEMP_M & S_IXOTH) result.oth_x = true;
	return result;
}

TFilesystemStats T_CLASS(TFilesystemStats, constructor)(TMessage parent_path, const TDirEntity entity)
{
	TFilesystemStats stats = { nullptr, kFSTypeUnknown, T_CLASS(TFilesystemPermissions, default_constructor)(), 0 };
	if (parent_path) stats.path = T_CLASS(TString, constructor)("%s/%s", parent_path, entity->d_name);
	else stats.path = T_CLASS(TString, constructor)("%s", entity->d_name);
	struct stat extra_stats;
	if (!lstat(stats.path, &extra_stats))
	{
		stats.permissions = T_CLASS(TFilesystemPermissions, constructor)(extra_stats);
		stats.type = T_CLASS(TFilesystemStats, type)(extra_stats);
		stats.size = extra_stats.st_size;
	} else T_THROW_EXCEPTION("Stat", stats.path, false, 0x00112233,)
	return stats;
}

TDirContent T_CLASS(TDirContent, constructor)(TMessage path)
{
	TDirContent result = T_CONTAINER(TVector, TFilesystemStats, default_constructor)();
	TDirEntity entity;
	TDir directory = T_CLASS(TDir, open)(path, true);
	while ((entity = readdir(directory)))
		T_CONTAINER(TVector, TFilesystemStats, append)(result, T_CLASS(TFilesystemStats, constructor)(path, entity), true);
	T_CLASS(TDir, close)(directory, true);
	return result;
}

void T_CLASS(TDirContent, clear)(TDirContent const content)
{
	FOR_EACH_ITERATOR_FROM(entity, TVector, TFilesystemStats, content)
		T_CLASS(TString, destructor)(entity->path);
}

TDirContent T_CLASS(TDirContent, destructor)(TDirContent const content)
{
	T_CLASS(TDirContent, clear)(content);
	return T_CONTAINER(TVector, TFilesystemStats, destructor)(content);
}

/*void T_CLASS(TDirContent, print)(TDirContent const content, const TConsoleId id)
{
	if (T_CONTAINER(TVector, TFilesystemStats, is_empty)(content))
		T_RETURN_VOID(T_CLASS(TConsole, print)(id, "Directory is empty!\n");)
	T_CLASS(TConsole, print)(id, " Permissions: | Type | Size | Name:\n");
	FOR_EACH_ITERATOR_FROM(entity, TVector, TFilesystemStats, content)
	{
#define T_PERMS entity->permissions
		T_CLASS(TConsole, print)(id, "%d%d%d ", T_PERMS.set_uid, T_PERMS.set_gid, T_PERMS.sticky_bit);
		T_CLASS(TConsole, print)(id, "%d%d%d", T_PERMS.usr_r, T_PERMS.usr_w, T_PERMS.usr_x);
		T_CLASS(TConsole, print)(id, "%d%d%d", T_PERMS.grp_r, T_PERMS.grp_w, T_PERMS.grp_x);
		T_CLASS(TConsole, print)(id, "%d%d%d", T_PERMS.oth_r, T_PERMS.oth_w, T_PERMS.oth_x);
		T_CLASS(TConsole, print)(id, " | %d | %ld | %s", entity->type, entity->size, entity->path);
		if (entity->type == kFSTypeSymbolicLink)
		{
			char temp_buffer[512 + 1];
			readlink(entity->path, temp_buffer, 512);
			T_CLASS(TConsole, print)(id, " -> %s", temp_buffer);
		}
		T_CLASS(TConsole, print)(id, "\n");
	}
}*/

void T_CLASS(TFilesystemStats, print)(const TFilesystemStats* const entity)
{
	T_CLASS(TConsole, print)(kLog, "%d%d%d ", entity->permissions.set_uid, entity->permissions.set_gid, entity->permissions.sticky_bit);
	T_CLASS(TConsole, print)(kLog, "%d%d%d", entity->permissions.usr_r, entity->permissions.usr_w, entity->permissions.usr_x);
	T_CLASS(TConsole, print)(kLog, "%d%d%d", entity->permissions.grp_r, entity->permissions.grp_w, entity->permissions.grp_x);
	T_CLASS(TConsole, print)(kLog, "%d%d%d", entity->permissions.oth_r, entity->permissions.oth_w, entity->permissions.oth_x);
	T_CLASS(TConsole, print)(kLog, " | %d | %ld | %s", entity->type, entity->size, entity->path);
	if (entity->type == kFSTypeSymbolicLink)
	{
		char temp_buffer[512 + 1];
		readlink(entity->path, temp_buffer, 512);
		T_CLASS(TConsole, print)(kLog, " -> %s", temp_buffer);
	}
	T_CLASS(TConsole, print)(kLog, "\n");
}

void T_CLASS(TDirContent, dirwalk)(TDirContent const content, const TBool follow_dirs, void (*action)(const TFilesystemStats* const))
{
	if (T_CONTAINER(TVector, TFilesystemStats, is_empty)(content))
		T_RETURN_VOID(T_CLASS(TConsole, print)(kLog, "Directory is empty!\n");)
	FOR_EACH_ITERATOR_FROM(entity, TVector, TFilesystemStats, content)
	{
		if (follow_dirs && entity->type == kFSTypeDirectory) {
			TDirContent temp_dir_content = T_CLASS(TDirContent, constructor)(entity->path);
			T_CLASS(TDirContent, dirwalk)(temp_dir_content, true, action);
			T_CLASS(TDirContent, destructor)(temp_dir_content);
		}
		action(entity);
	}
}
