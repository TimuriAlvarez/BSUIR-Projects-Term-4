#pragma once

#include <sys/types.h>

/*sys_types.h(0P)			POSIX Programmer's Manual		  sys_types.h(0P)

PROLOG			top

		This manual page is part of the POSIX Programmer's Manual.  The
		Linux implementation of this interface may differ (consult the
		corresponding Linux manual page for details of Linux behavior),
		or the interface may not be implemented on Linux.

NAME			top

		sys/types.h — data types

SYNOPSIS			top

		#include <sys/types.h>

DESCRIPTION			top

		The <sys/types.h> header shall define at least the following
		types:*/

		typedef int blkcnt_t;		//  Used for file block counts.

		typedef int blksize_t;		// Used for block sizes.

		typedef int clock_t;			//Used for system times in clock ticks or
						//CLOCKS_PER_SEC; see <time.h>.

		typedef int clockid_t;		// Used for clock ID type in the clock and timer
						//functions.

		//typedef int dev_t;			//  Used for device IDs.

		typedef unsigned int fsblkcnt_t;		//Used for file system block counts.

		typedef unsigned int fsfilcnt_t;		//Used for file system file counts.

		typedef int gid_t;			//  Used for group IDs.

		typedef int id_t;			//	Used as a general identifier; can be used to
						//contain at least a pid_t, uid_t, or gid_t.

		//typedef unsigned int ino_t;			//  Used for file serial numbers.

		typedef int key_t;			//  Used for XSI interprocess communication.

		//typedef int mode_t;			// Used for some file attributes.

		typedef int nlink_t;			//Used for link counts.

		//typedef int off_t;			//  Used for file sizes.

		//typedef int pid_t;			//  Used for process IDs and process group IDs.

		typedef int pthread_attr_t;  //Used to identify a thread attribute object.

		typedef int pthread_barrier_t;
						//Used to identify a barrier.

		typedef int pthread_barrierattr_t;
						//Used to define a barrier attributes object.

		typedef int pthread_cond_t;  //Used for condition variables.

		typedef int pthread_condattr_t;
						//Used to identify a condition attribute object.

		typedef int pthread_key_t;	//Used for thread-specific data keys.

		typedef int pthread_mutex_t; //Used for mutexes.

		typedef int pthread_mutexattr_t;
						//Used to identify a mutex attribute object.

		typedef int pthread_once_t;  //Used for dynamic package initialization.

		typedef int pthread_rwlock_t;
						//Used for read-write locks.

		typedef int pthread_rwlockattr_t;
						//Used for read-write lock attributes.

		typedef int pthread_spinlock_t;
						//Used to identify a spin lock.

		typedef int pthread_t;		// Used to identify a thread.

		//typedef unsigned int size_t;			// Used for sizes of objects.

		//typedef int ssize_t;			//Used for a count of bytes or an error indication.

		typedef int suseconds_t;		//Used for time in microseconds.

		//typedef int time_t;			// Used for time in seconds.

		typedef int timer_t;			//Used for timer ID returned by timer_create().

		typedef int trace_attr_t;	// Used to identify a trace stream attributes object

		typedef int trace_event_id_t;
						//Used to identify a trace event type.

		typedef int trace_event_set_t;
						//Used to identify a trace event type set.

		typedef int trace_id_t;		//Used to identify a trace stream.

		typedef int uid_t;			//  Used for user IDs.

/*		All of the types shall be defined as arithmetic types of an
		appropriate length, with the following exceptions:*/

		typedef int pthread_attr_t;
		typedef int pthread_barrier_t;
		typedef int pthread_barrierattr_t;
		typedef int pthread_cond_t;
		typedef int pthread_condattr_t;
		typedef int pthread_key_t;
		typedef int pthread_mutex_t;
		typedef int pthread_mutexattr_t;
		typedef int pthread_once_t;
		typedef int pthread_rwlock_t;
		typedef int pthread_rwlockattr_t;
		typedef int pthread_spinlock_t;
		typedef int pthread_t;
		typedef int timer_t;
		typedef int trace_attr_t;
		typedef int trace_event_id_t;
		typedef int trace_event_set_t;
		typedef int trace_id_t;

/*		Additionally:*/

		//typedef int  mode_t; //shall be an integer type.

		//typedef int  dev_t; //shall be an integer type.

		typedef int  nlink_t, uid_t, gid_t, id_t; // shall be integer types.

		typedef int  blkcnt_t;//, off_t;// shall be signed integer types.

		//typedef unsigned int  fsblkcnt_t, fsfilcnt_t, ino_t; //shall be defined as
			//unsigned integer types.

		//typedef unsigned int  size_t; //shall be an unsigned integer type.

		//typedef int  blksize_t, pid_t;//, ssize_t; //shall be signed integer types.

		typedef int  clock_t; //shall be an integer or real-floating type.  time_t
			//shall be an integer type.

/*		The type ssize_t shall be capable of storing values at least in
		the range [-1, {SSIZE_MAX}].

		The type suseconds_t shall be a signed integer type capable of
		storing values at least in the range [-1, 1000000].

		The implementation shall support one or more programming
		environments in which the widths of blksize_t, pid_t, size_t,
		ssize_t, and suseconds_t are no greater than the width of type
		long.  The names of these programming environments can be
		obtained using the confstr() function or the getconf utility.

		There are no defined comparison or assignment operators for the
		following types:*/

		typedef int pthread_attr_t;
		typedef int pthread_barrier_t;
		typedef int pthread_barrierattr_t;
		typedef int pthread_cond_t;
		typedef int pthread_condattr_t;
		typedef int pthread_mutex_t;
		typedef int pthread_mutexattr_t;
		typedef int pthread_rwlock_t;
		typedef int pthread_rwlockattr_t;
		typedef int pthread_spinlock_t;
		typedef int timer_t;
		typedef int trace_attr_t;

/*		The following sections are informative.

APPLICATION USAGE			top

		None.

RATIONALE			top

		None.

FUTURE DIRECTIONS			top

		None.

SEE ALSO			top

		time.h(0p)

		The System Interfaces volume of POSIX.1‐2017, confstr(3p)

		The Shell and Utilities volume of POSIX.1‐2017, getconf(1p)

COPYRIGHT			top

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

IEEE/The Open Group					2017						 sys_types.h(0P)*/
