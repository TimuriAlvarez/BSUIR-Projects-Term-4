#pragma once

#include "sys/types.h"

/*PROLOG         top

       This manual page is part of the POSIX Programmer's Manual.  The
       Linux implementation of this interface may differ (consult the
       corresponding Linux manual page for details of Linux behavior),
       or the interface may not be implemented on Linux.

NAME         top

       termios.h — define values for termios

SYNOPSIS         top

#include <sys/types.h>
       #include <termios.h>

DESCRIPTION         top

       The <termios.h> header shall contain the definitions used by the
       terminal I/O interfaces (see Chapter 11, General Terminal
       Interface for the structures and names defined).

   The termios Structure
       The <termios.h> header shall define the following data types
       through typedef:
*/
       struct TempStruct
{
    int temp_int;
};
       typedef struct TempStruct cc_t;        //Used for terminal special characters.

       typedef struct TempStruct speed_t;     //Used for terminal baud rates.

       typedef struct TempStruct tcflag_t;    //Used for terminal modes.

/*       The above types shall be all unsigned integer types.

       The implementation shall support one or more programming
       environments in which the widths of cc_t, speed_t, and tcflag_t
       are no greater than the width of type long.  The names of these
       programming environments can be obtained using the confstr()
       function or the getconf utility.

       The <termios.h> header shall define the termios structure, which
       shall include at least the following members:*/
struct termios
{
    tcflag_t  c_iflag;//     Input modes.
    tcflag_t  c_oflag;//     Output modes.
    tcflag_t  c_cflag;//     Control modes.
    tcflag_t  c_lflag;//     Local modes.
    cc_t*      c_cc;//  Control characters.
};

/*       The <termios.h> header shall define the following symbolic
       constant:

       NCCS        Size of the array c_cc for control characters.

       The <termios.h> header shall define the following symbolic
       constants for use as subscripts for the array c_cc:

           ┌────────────────────────────────────┬──────────────────┐
           │          Subscript Usage           │                  │
           │Canonical Mode   Non-Canonical Mode │   Description    │
           ├───────────────┬────────────────────┼──────────────────┤
           │VEOF           │                    │ EOF character.   │
           │VEOL           │                    │ EOL character.   │
           │VERASE         │                    │ ERASE character. │
           │VINTR          │ VINTR              │ INTR character.  │
           │VKILL          │                    │ KILL character.  │
           │               │ VMIN               │ MIN value.       │
           │VQUIT          │ VQUIT              │ QUIT character.  │
           │VSTART         │ VSTART             │ START character. │
           │VSTOP          │ VSTOP              │ STOP character.  │
           │VSUSP          │ VSUSP              │ SUSP character.  │
           │               │ VTIME              │ TIME value.      │
           └───────────────┴────────────────────┴──────────────────┘
       The subscript values shall be suitable for use in #if
       preprocessing directives and shall be distinct, except that the
       VMIN and VTIME subscripts may have the same values as the VEOF
       and VEOL subscripts, respectively.

   Input Modes
       The <termios.h> header shall define the following symbolic
       constants for use as flags in the c_iflag field. The c_iflag
       field describes the basic terminal input control.

       BRKINT      Signal interrupt on break.

       ICRNL       Map CR to NL on input.

       IGNBRK      Ignore break condition.

       IGNCR       Ignore CR.

       IGNPAR      Ignore characters with parity errors.

       INLCR       Map NL to CR on input.

       INPCK       Enable input parity check.

       ISTRIP      Strip character.

       IXANY       Enable any character to restart output.

       IXOFF       Enable start/stop input control.

       IXON        Enable start/stop output control.

       PARMRK      Mark parity errors.

   Output Modes
       The <termios.h> header shall define the following symbolic
       constants for use as flags in the c_oflag field. The c_oflag
       field specifies the system treatment of output.

       OPOST       Post-process output.

       ONLCR       Map NL to CR-NL on output.

       OCRNL       Map CR to NL on output.

       ONOCR       No CR output at column 0.

       ONLRET      NL performs CR function.

       OFDEL       Fill is DEL.

       OFILL       Use fill characters for delay.

       NLDLY       Select newline delays:

                   NL0     Newline type 0.

                   NL1     Newline type 1.

       CRDLY       Select carriage-return delays:

                   CR0     Carriage-return delay type 0.

                   CR1     Carriage-return delay type 1.

                   CR2     Carriage-return delay type 2.

                   CR3     Carriage-return delay type 3.

       TABDLY      Select horizontal-tab delays:

                   TAB0    Horizontal-tab delay type 0.

                   TAB1    Horizontal-tab delay type 1.

                   TAB2    Horizontal-tab delay type 2.

                   TAB3    Expand tabs to spaces.

       BSDLY       Select backspace delays:

                   BS0     Backspace-delay type 0.

                   BS1     Backspace-delay type 1.

       VTDLY       Select vertical-tab delays:

                   VT0     Vertical-tab delay type 0.

                   VT1     Vertical-tab delay type 1.

       FFDLY       Select form-feed delays:

                   FF0     Form-feed delay type 0.

                   FF1     Form-feed delay type 1.

   Baud Rate Selection
       The <termios.h> header shall define the following symbolic
       constants for use as values of objects of type speed_t.

       The input and output baud rates are stored in the termios
       structure. These are the valid values for objects of type
       speed_t.  Not all baud rates need be supported by the underlying
       hardware.

       B0          Hang up

       B50         50 baud

       B75         75 baud

       B110        110 baud

       B134        134.5 baud

       B150        150 baud

       B200        200 baud

       B300        300 baud

       B600        600 baud

       B1200       1200 baud

       B1800       1800 baud

       B2400       2400 baud

       B4800       4800 baud

       B9600       9600 baud

       B19200      19200 baud

       B38400      38400 baud

   Control Modes
       The <termios.h> header shall define the following symbolic
       constants for use as flags in the c_cflag field. The c_cflag
       field describes the hardware control of the terminal; not all
       values specified are required to be supported by the underlying
       hardware.

       CSIZE       Character size:

                   CS5     5 bits

                   CS6     6 bits

                   CS7     7 bits

                   CS8     8 bits

       CSTOPB      Send two stop bits, else one.

       CREAD       Enable receiver.

       PARENB      Parity enable.

       PARODD      Odd parity, else even.

       HUPCL       Hang up on last close.

       CLOCAL      Ignore modem status lines.

       The implementation shall support the functionality associated
       with the symbols CS7, CS8, CSTOPB, PARODD, and PARENB.

   Local Modes
       The <termios.h> header shall define the following symbolic
       constants for use as flags in the c_lflag field. The c_lflag
       field of the argument structure is used to control various
       terminal functions.

       ECHO        Enable echo.

       ECHOE       Echo erase character as error-correcting backspace.

       ECHOK       Echo KILL.

       ECHONL      Echo NL.

       ICANON      Canonical input (erase and kill processing).

       IEXTEN      Enable extended input character processing.

       ISIG        Enable signals.

       NOFLSH      Disable flush after interrupt or quit.

       TOSTOP      Send SIGTTOU for background output.

   Attribute Selection
       The <termios.h> header shall define the following symbolic
       constants for use with tcsetattr():

       TCSANOW     Change attributes immediately.

       TCSADRAIN   Change attributes when output has drained.

       TCSAFLUSH   Change attributes when output has drained; also flush
                   pending input.

   Line Control
       The <termios.h> header shall define the following symbolic
       constants for use with tcflush():

       TCIFLUSH    Flush pending input.

       TCIOFLUSH   Flush both pending input and untransmitted output.

       TCOFLUSH    Flush untransmitted output.

       The <termios.h> header shall define the following symbolic
       constants for use with tcflow():

       TCIOFF      Transmit a STOP character, intended to suspend input
                   data.

       TCION       Transmit a START character, intended to restart input
                   data.

       TCOOFF      Suspend output.

       TCOON       Restart output.

       The <termios.h> header shall define the pid_t type as described
       in <sys/types.h>.

       The following shall be declared as functions and may also be
       defined as macros. Function prototypes shall be provided.*/

           speed_t cfgetispeed(const struct termios *);
           speed_t cfgetospeed(const struct termios *);
           int     cfsetispeed(struct termios *, speed_t);
           int     cfsetospeed(struct termios *, speed_t);
           int     tcdrain(int);
           int     tcflow(int, int);
           int     tcflush(int, int);
           int     tcgetattr(int, struct termios *);
           pid_t   tcgetsid(int);
           int     tcsendbreak(int, int);
           int     tcsetattr(int, int, const struct termios *);

/*       The following sections are informative.

APPLICATION USAGE         top

       The following names are reserved for XSI-conformant systems to
       use as an extension to the above; therefore strictly conforming
       applications shall not use them:

       CBAUD      EXTB       VDSUSP
       DEFECHO    FLUSHO     VLNEXT
       ECHOCTL    LOBLK      VREPRINT
       ECHOKE     PENDIN     VSTATUS
       ECHOPRT    SWTCH      VWERASE
       EXTA       VDISCARD

RATIONALE         top

       None.

FUTURE DIRECTIONS         top

       None.

SEE ALSO         top

       sys_types.h(0p)

       The System Interfaces volume of POSIX.1‐2017, cfgetispeed(3p),
       cfgetospeed(3p), cfsetispeed(3p), cfsetospeed(3p), confstr(3p),
       tcdrain(3p), tcflow(3p), tcflush(3p), tcgetattr(3p),
       tcgetsid(3p), tcsendbreak(3p), tcsetattr(3p)

       The Shell and Utilities volume of POSIX.1‐2017, Chapter 11,
       General Terminal Interface, getconf(1p)

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

IEEE/The Open Group               2017                     termios.h(0P)*/
