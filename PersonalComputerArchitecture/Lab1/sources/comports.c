#include "tlib.h"

#define T_THROW_PORT_OPENING(port_path) T_THROW_EXCEPTION(port_path,  "Unable to  open provided port", E_LOCATION, true, 0xCE0100, 0)

int port_close(TFileDescriptor fd)
{
	return close(fd);
}

TFileDescriptor port_open(const unsigned short int port_number)
{
	TString port_path = T_CLASS(TString, constructor)("/dev/tnt");
	port_path = T_CLASS(TString, append)(port_path, (char)('0' + port_number));
	TFileDescriptor fd = open(port_path, O_RDWR | O_NOCTTY | O_NDELAY); /* File descriptor for the port */
	if (fd == -1) T_THROW_PORT_OPENING(port_path)
	else fcntl(fd, F_SETFL, 0);
	T_CLASS(TString, destructor)(port_path);
	return fd;
}
void port_write(TFileDescriptor fd, TMessage message)
{
	const int n = write(fd, message, T_CLASS(TString, size)(message) + 1);
	if (n < 0) fputs("writing to port has failed!\n", stderr);
}
TString port_read(TFileDescriptor fd)
{
	fcntl(fd, F_SETFL, 0);
	TString str = nullptr;
	while (true)
	{
		char c;
		read(fd, &c, sizeof(char));
		if (c == '\0') break;
		str = T_CLASS(TString, append)(str, c);
	}
	return str;
}
