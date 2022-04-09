#pragma once

#include "../../../TLibLibraryC/tlib.h"
#include "../../../TLinuxInterfaceC/tlinux.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */

#ifdef __linux__
#include <unistd.h>  /* UNIX standard function definitions */
#include <termios.h> /* POSIX terminal control definitions */
#endif

T_IMPORT_MENU_DECLARATION(void)

int port_close(TFileDescriptor fd);
TFileDescriptor port_open(const unsigned short int port_number);
void port_write(TFileDescriptor fd, TMessage message);
TString port_read(TFileDescriptor fd);

void writing_mode(void* const parameters);
void reading_mode(void* const parameters);
