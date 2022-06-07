#pragma once

#include <sys/stat.h>
#include "../tfilesystem.h"

/*	┌────────┬───────────────┬──────────────────────────────────────────────┐
	│ Name   │ Numeric Value │                 Description                  │
	├────────┼───────────────┼──────────────────────────────────────────────┤
	│S_IRWXU │      0700     │ Read, write, execute/search by owner.        │
	│S_IRUSR │      0400     │ Read permission, owner.                      │
	│S_IWUSR │      0200     │ Write permission, owner.                     │
	│S_IXUSR │      0100     │ Execute/search permission, owner.            │
	├────────┼───────────────┼──────────────────────────────────────────────┤
	│S_IRWXG │       070     │ Read, write, execute/search by group.        │
	│S_IRGRP │       040     │ Read permission, group.                      │
	│S_IWGRP │       020     │ Write permission, group.                     │
	│S_IXGRP │       010     │ Execute/search permission, group.            │
	├────────┼───────────────┼──────────────────────────────────────────────┤
	│S_IRWXO │        07     │ Read, write, execute/search by others.       │
	│S_IROTH │        04     │ Read permission, others.                     │
	│S_IWOTH │        02     │ Write permission, others.                    │
	│S_IXOTH │        01     │ Execute/search permission, others.           │
	├────────┼───────────────┼──────────────────────────────────────────────┤
	│S_ISUID │     04000     │ Set-user-ID on execution.                    │
	│S_ISGID │     02000     │ Set-group-ID on execution.                   │
	│S_ISVTX │     01000     │ On directories, restricted deletion flag.    │
	└────────┴───────────────┴──────────────────────────────────────────────┘	*/

typedef struct
{
	TBool				set_uid, set_gid, sticky_bit;
	TBool				usr_r, usr_w, usr_x;
	TBool				grp_r, grp_w, grp_x;
	TBool				oth_r, oth_w, oth_x;
} TFilesystemPermissions;

typedef struct
{
	TString					path;
	TFilesystemType			type;
	TFilesystemPermissions	permissions;
	ullint					size;
} TFilesystemStats;

#define CONTAINER_DATA_TYPE TFilesystemStats
#include "../../../TContainersC/timport/tvector.h"

typedef T_CONTAINER(TVector, TFilesystemStats, T_CONTAINER_POSTFIX) TDirContent;


TDirContent T_CLASS(TDirContent, constructor)(TMessage path);

TDirContent T_CLASS(TDirContent, destructor)(TDirContent content);

void T_CLASS(TDirContent, print)(TDirContent const content, const TConsoleId id);

void T_CLASS(TFilesystemStats, print)(const TFilesystemStats* const entity);
void T_CLASS(TDirContent, dirwalk)(TDirContent const content, const TBool follow_dirs, void (*action)(const TFilesystemStats* const));
