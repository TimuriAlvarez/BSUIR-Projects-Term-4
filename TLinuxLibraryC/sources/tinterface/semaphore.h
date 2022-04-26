#pragma once

#include <semaphore.h>

#include "sys/types.h"

/*semaphore.h(0P)         POSIX Programmer's Manual        semaphore.h(0P)

PROLOG         top

	   This manual page is part of the POSIX Programmer's Manual.  The
	   Linux implementation of this interface may differ (consult the
	   corresponding Linux manual page for details of Linux behavior),
	   or the interface may not be implemented on Linux.

NAME         top

	   semaphore.h — semaphores

SYNOPSIS         top

	   #include <semaphore.h>

DESCRIPTION         top

	   The <semaphore.h> header shall define the sem_t type, used in
	   performing semaphore operations. The semaphore may be implemented
	   using a file descriptor, in which case applications are able to
	   open up at least a total of {OPEN_MAX} files and semaphores.

	   The <semaphore.h> header shall define the symbolic constant
	   SEM_FAILED which shall have type sem_t *.*/

/*	   The following shall be declared as functions and may also be
	   defined as macros. Function prototypes shall be provided.*/

		   int    sem_close(sem_t *);
		   int    sem_destroy(sem_t *);
		   int    sem_getvalue(sem_t *restrict, int *restrict_2);
		   int    sem_init(sem_t *, int, unsigned);
		   //sem_t *sem_open(const char *, int, ...);
		   int    sem_post(sem_t *);
		   //int    sem_timedwait(sem_t *restrict, const struct timespec *restrict_2);
		   int    sem_trywait(sem_t *);
		   int    sem_unlink(const char *);
		   int    sem_wait(sem_t *);

/*	   Inclusion of the <semaphore.h> header may make visible symbols
	   defined in the <fcntl.h> and <time.h> headers.

	   The following sections are informative.

APPLICATION USAGE         top

	   None.

RATIONALE         top

	   None.

FUTURE DIRECTIONS         top

	   None.

SEE ALSO         top

	   fcntl.h(0p), sys_types.h(0p), time.h(0p)

	   The System Interfaces volume of POSIX.1‐2017, sem_close(3p),
	   sem_destroy(3p), sem_getvalue(3p), sem_init(3p), sem_open(3p),
	   sem_post(3p), sem_timedwait(3p), sem_trywait(3p), sem_unlink(3p)

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

IEEE/The Open Group               2017                   semaphore.h(0P)*/
