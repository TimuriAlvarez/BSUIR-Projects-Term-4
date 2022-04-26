#pragma once

#include <dirent.h>

#include "sys/types.h"

/*dirent.h(0P)            POSIX Programmer's Manual           dirent.h(0P)

PROLOG         top

	   This manual page is part of the POSIX Programmer's Manual.  The
	   Linux implementation of this interface may differ (consult the
	   corresponding Linux manual page for details of Linux behavior),
	   or the interface may not be implemented on Linux.

NAME         top

	   dirent.h — format of directory entries

SYNOPSIS         top

	   #include <dirent.h>

DESCRIPTION         top

	   The internal format of directories is unspecified.

	   The <dirent.h> header shall define the following type:*/

typedef struct DIR DIR;     /*A type representing a directory stream. The DIR type may
			   be an incomplete type.

	   It shall also define the structure dirent which shall include the
	   following members:

	   In the glibc implementation, the dirent structure is defined as
	   follows:*/

struct dirent
{
	ino_t          d_ino;       /* This is the inode number of the file. */
	off_t          d_off;       /* The value returned in d_off is the same as would be
								   returned by calling telldir(3) at the current position in
								   the directory stream.  Be aware that despite its type and
								   name, the d_off field is seldom any kind of directory
								   offset on modern filesystems.  Applications should treat
								   this field as an opaque value, making no assumptions about
								   its contents; see also telldir(3). */
	unsigned short d_reclen;    /* This is the size (in bytes) of the returned record.  This
								   may not match the size of the structure definition shown
								   above; see NOTES. */
	unsigned char  d_type;      /* Type of file; not supported
								   by all filesystem types
								   This field contains a value indicating the file type,
								   making it possible to avoid the expense of calling
								   lstat(2) if further actions depend on the type of the
								   file.
								   When a suitable feature test macro is defined
								   (_DEFAULT_SOURCE on glibc versions since 2.19, or
								   _BSD_SOURCE on glibc versions 2.19 and earlier), glibc
								   defines the following macro constants for the value
								   returned in d_type:

								   DT_BLK		This is a block device.
								   DT_CHR		This is a character device.
								   DT_DIR		This is a directory.
								   DT_FIFO		This is a named pipe (FIFO).
								   DT_LNK		This is a symbolic link.
								   DT_REG		This is a regular file.
								   DT_SOCK		This is a UNIX domain socket.
								   DT_UNKNOWN	The file type could not be determined.

								   Currently, only some filesystems (among them: Btrfs, ext2,
								   ext3, and ext4) have full support for returning the file
								   type in d_type.  All applications must properly handle a
								   return of DT_UNKNOWN. */
	char           d_name[256]; /* This field contains the null terminated filename.  See
								   NOTES. */
};

/*	   The <dirent.h> header shall define the ino_t type as described in
	   <sys/types.h>.

	   The array d_name is of unspecified size, but shall contain a
	   filename of at most {NAME_MAX} bytes followed by a terminating
	   null byte.

	   The following shall be declared as functions and may also be
	   defined as macros. Function prototypes shall be provided.*/

		   int            alphasort(const struct dirent **, const struct dirent **);
		   int            closedir(DIR *);
		   int            dirfd(DIR *);
		   DIR           *fdopendir(int);
		   DIR           *opendir(const char *);
		   struct dirent *readdir(DIR *);
		   int            readdir_r(DIR *restrict, struct dirent *restrict_2, struct dirent **restrict_3);
		   void           rewinddir(DIR *);
		   int            scandir(const char *, struct dirent ***, int (*)(const struct dirent *), int (*)(const struct dirent **, const struct dirent **));
		   void           seekdir(DIR *, long);
		   long           telldir(DIR *);

/*	   The following sections are informative.

APPLICATION USAGE         top

	   None.

RATIONALE         top

	   Information similar to that in the <dirent.h> header is contained
	   in a file <sys/dir.h> in 4.2 BSD and 4.3 BSD. The equivalent in
	   these implementations of struct dirent from this volume of
	   POSIX.1‐2017 is struct direct.  The filename was changed because
	   the name <sys/dir.h> was also used in earlier implementations to
	   refer to definitions related to the older access method; this
	   produced name conflicts. The name of the structure was changed
	   because this volume of POSIX.1‐2017 does not completely define
	   what is in the structure, so it could be different on some
	   implementations from struct direct.

	   The name of an array of char of an unspecified size should not be
	   used as an lvalue. Use of:

		   sizeof(d_name)

	   is incorrect; use:

		   strlen(d_name)

	   instead.

	   The array of char d_name is not a fixed size. Implementations may
	   need to declare struct dirent with an array size for d_name of 1,
	   but the actual number of bytes provided matches (or only slightly
	   exceeds) the length of the filename string.

FUTURE DIRECTIONS         top

	   None.

SEE ALSO         top

	   sys_types.h(0p)

	   The System Interfaces volume of POSIX.1‐2017, alphasort(3p),
	   closedir(3p), dirfd(3p), fdopendir(3p), readdir(3p),
	   rewinddir(3p), seekdir(3p), telldir(3p)

COPYRIGHT         top

	   Portions of this text are reprinted and reproduced in electronic
	   form from IEEE Std 1003.1-2017, Standard for Information
	   Technology -- Portable Operating System Interface (POSIX), The
	   Open Group Base Specifications Issue 7, 2018 Edition, Copyright
	   (C) 2018 by the Institute of Electrical and Electronics
	   Engineers, Inc and The Open Group.  In the event of any
	   discrepancy between this version and the original IEEE and The
	   Open Group Standard, the original IEEE and The Open Group
	   Standard is the referee document. The original Standard can be
	   obtained online at http://www.opengroup.org/unix/online.html .

	   Any typographical or formatting errors that appear in this page
	   are most likely to have been introduced during the conversion of
	   the source files to man page format. To report such errors, see
	   https://www.kernel.org/doc/man-pages/reporting_bugs.html .

IEEE/The Open Group               2017                      dirent.h(0P)*/
