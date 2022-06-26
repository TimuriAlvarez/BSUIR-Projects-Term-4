#include "../tlinux.h"

int main(void)
{
	T_CLASS(syscall, execute)("ls ~/ddtest -lha");
	TDirContent content = T_CLASS(TDirContent, constructor)("/home/timurialvarez/ddtest");

	T_CLASS(TDirContent, dirwalk)(content, true, T_CLASS(TFilesystemStats, print), true);
	T_CLASS(TDirContent, destructor)(content);
	return 0;
}
