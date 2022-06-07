#pragma once

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef enum
{
	kFSTypeBlockSpecialFile,
	kFSTypeCharacterSpecialFile,
	kFSTypeDirectory,
	kFSTypeFIFOFile, // AKA kFSTypePipeFile
	kFSTypeRegularFile,
	kFSTypeSymbolicLink,
	kFSTypeDomainSocket,
	kFSTypeIPCMessageQueue,
	kFSTypeIPCSemaphore,
	kFSTypeIPCSharedMemoryObject,
	kFSTypeIPCTypedMemoryObject,
	//kFSTypeWhiteoutInode, - internal to the implementation and should not be seen in normal user applications
	kFSTypeUnknown
} TFilesystemType;

typedef DIR*	TDir;
