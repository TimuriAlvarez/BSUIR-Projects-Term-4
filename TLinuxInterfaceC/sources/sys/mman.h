#pragma once

#include "types.h"

/*sys_mman.h(0P)          POSIX Programmer's Manual         sys_mman.h(0P)

PROLOG         top

	   This manual page is part of the POSIX Programmer's Manual.  The
	   Linux implementation of this interface may differ (consult the
	   corresponding Linux manual page for details of Linux behavior),
	   or the interface may not be implemented on Linux.

NAME         top

	   sys/mman.h — memory management declarations

SYNOPSIS         top

	   #include <sys/mman.h>

DESCRIPTION         top

	   The <sys/mman.h> header shall define the following symbolic
	   constants for use as protection options:*/

#define PROT_EXEC 0x01      //Page can be executed.

#define PROT_NONE 0x02    //Page cannot be accessed.

#define PROT_READ 0x03    //Page can be read.

#define PROT_WRITE 0x04   //Page can be written.

/*	   The <sys/mman.h> header shall define the following symbolic
	   constants for use as flag options:*/

#define MAP_FIXED 0x05    //Interpret addr exactly.

#define MAP_PRIVATE 0x06  //Changes are private.

#define MAP_SHARED 0x07   //Share changes.

/*	   The <sys/mman.h> header shall define the following symbolic
	   constants for the msync() function:*/

#define MS_ASYNC 0x08     //Perform asynchronous writes.

#define MS_INVALIDATE 0x09 //Invalidate mappings.

#define MS_SYNC 0x0A      //Perform synchronous writes.

/*	   The <sys/mman.h> header shall define the following symbolic
	   constants for the mlockall() function:*/

#define MCL_CURRENT 0x0B  //Lock currently mapped pages.

#define MCL_FUTURE 0x0C   //Lock pages that become mapped.

/*	   The <sys/mman.h> header shall define the symbolic constant
	   MAP_FAILED which shall have type void * and shall be used to
	   indicate a failure from the mmap() function .*/

#define MAP_FAILED 0x0D

/*	   If the Advisory Information option is supported, the <sys/mman.h>
	   header shall define symbolic constants for the advice argument to
	   the posix_madvise() function as follows:*/

#define POSIX_MADV_DONTNEED 0x0E
			 /*The application expects that it will not access the
			 specified range in the near future.*/

#define POSIX_MADV_NORMAL 0x0F
			 /*The application has no advice to give on its behavior with
			 respect to the specified range. It is the default
			 characteristic if no advice is given for a range of memory.*/

#define POSIX_MADV_RANDOM 0x10
			 /*The application expects to access the specified range in a
			 random order.*/

#define POSIX_MADV_SEQUENTIAL 0x11
			 /*The application expects to access the specified range
			 sequentially from lower addresses to higher addresses.*/

#define POSIX_MADV_WILLNEED 0x12
			 /*The application expects to access the specified range in
			 the near future.*/

/*	   The <sys/mman.h> header shall define the following symbolic
	   constants for use as flags for the posix_typed_mem_open()
	   function:*/

#define POSIX_TYPED_MEM_ALLOCATE 0x13
			 /*Allocate on mmap().*/

#define POSIX_TYPED_MEM_ALLOCATE_CONTIG 0x14
			 /*Allocate contiguously on mmap().*/

#define POSIX_TYPED_MEM_MAP_ALLOCATABLE 0x15
			 /*Map on mmap(), without affecting allocatability.*/

/*	   The <sys/mman.h> header shall define the mode_t, off_t, and
	   size_t types as described in sys_types.h(0p).

	   The <sys/mman.h> header shall define the posix_typed_mem_info
	   structure, which shall include at least the following member:*/

	   struct posix_typed_mem_info
	   {
		   size_t  posix_tmi_length;  /*Maximum length which may be allocated
									 from a typed memory object.*/
	   };

/*	   The following shall be declared as functions and may also be
	   defined as macros. Function prototypes shall be provided.*/

		   int    mlock(const void *, size_t);
		   int    mlockall(int);
		   void  *mmap(void *, size_t, int, int, int, off_t);
		   int    mprotect(void *, size_t, int);
		   int    msync(void *, size_t, int);
		   int    munlock(const void *, size_t);
		   int    munlockall(void);
		   int    munmap(void *, size_t);
		   int    posix_madvise(void *, size_t, int);
		   int    posix_mem_offset(const void *restrict, size_t, off_t *restrict2,
					  size_t *restrict3, int *restrict4);
		   int    posix_typed_mem_get_info(int, struct posix_typed_mem_info *);
		   int    posix_typed_mem_open(const char *, int, int);
		   int    shm_open(const char *, int, mode_t);
		   int    shm_unlink(const char *);

/*	   The following sections are informative.

APPLICATION USAGE         top

	   None.

RATIONALE         top

	   None.

FUTURE DIRECTIONS         top

	   None.

SEE ALSO         top

	   sys_types.h(0p)

	   The System Interfaces volume of POSIX.1‐2017, mlock(3p),
	   mlockall(3p), mmap(3p), mprotect(3p), msync(3p), munmap(3p),
	   posix_madvise(3p), posix_mem_offset(3p),
	   posix_typed_mem_get_info(3p), posix_typed_mem_open(3p),
	   shm_open(3p), shm_unlink(3p)

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

IEEE/The Open Group               2017                    sys_mman.h(0P)*/
