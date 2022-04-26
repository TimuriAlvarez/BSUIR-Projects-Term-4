#pragma once

#include "types.h"

/*sys_ipc.h(0P)           POSIX Programmer's Manual          sys_ipc.h(0P)

PROLOG         top

	   This manual page is part of the POSIX Programmer's Manual.  The
	   Linux implementation of this interface may differ (consult the
	   corresponding Linux manual page for details of Linux behavior),
	   or the interface may not be implemented on Linux.

NAME         top

	   sys/ipc.h — XSI interprocess communication access structure

SYNOPSIS         top

	   #include <sys/ipc.h>

DESCRIPTION         top

	   The <sys/ipc.h> header is used by three mechanisms for XSI
	   interprocess communication (IPC): messages, semaphores, and
	   shared memory. All use a common structure type, ipc_perm, to pass
	   information used in determining permission to perform an IPC
	   operation.

	   The <sys/ipc.h> header shall define the ipc_perm structure, which
	   shall include the following members:*/

struct  ipc_perm
{
		   uid_t    uid;    //Owner's user ID.
		   gid_t    gid;    //Owner's group ID.
		   uid_t    cuid;   //Creator's user ID.
		   gid_t    cgid;   //Creator's group ID.
		   mode_t   mode;   //Read/write permission.
};

/*	   The <sys/ipc.h> header shall define the uid_t, gid_t, mode_t, and
	   key_t types as described in <sys/types.h>.

	   The <sys/ipc.h> header shall define the following symbolic
	   constants.

	   Mode bits:*/

#define IPC_CREAT 0xFFFF  //Create entry if key does not exist.

#define IPC_EXCL 0xFFFF   //Fail if key exists.

#define IPC_NOWAIT 0xFFFF //Error if request must wait.

//	   Keys:

#define IPC_PRIVATE 0xFFFF //Private key.

//	   Control commands:

#define IPC_RMID 0xFFFF   //Remove identifier.

#define IPC_SET 0xFFFF    //Set options.

#define IPC_STAT 0xFFFF   //Get options.

/*	   The following shall be declared as a function and may also be
	   defined as a macro. A function prototype shall be provided.*/

		   key_t  ftok(const char *, int);

/*	   The following sections are informative.

APPLICATION USAGE         top

	   None.

RATIONALE         top

	   None.

FUTURE DIRECTIONS         top

	   None.

SEE ALSO         top

	   sys_types.h(0p)

	   The System Interfaces volume of POSIX.1‐2017, ftok(3p)

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

IEEE/The Open Group               2017                     sys_ipc.h(0P)*/
