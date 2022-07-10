#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "tlib.h"

int menu_help(void)
{
	T_CLASS(TConsole, print)(kOutput,
							 "Available parameters:\n"
							 "\t/l - list (print) files available for processing;\n"
							 "\t[ file_name ] - process the file;\n"
							 "\t/g - generate/regenerate file;\n"
							 "\t/c - clear temp and res files;\n"
							 "\t/h - show this message (help).\n");
	return 0;
}
typedef struct stat TFileStat;
void menu_list(void)
{
	T_FUNCTION(syscall, execute)("ls -1 temp");
}
void menu_generate(void)
{
	T_FUNCTION(syscall, execute)("make generate");
}
void menu_clear(void)
{
	T_FUNCTION(syscall, execute)("rm -f temp/*");
}

void threads_start(const lint size, const TFileDescriptor fd);

void process_file(TMessage file_path)
{
	TFileDescriptor fd = open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
	TFileStat sb;
	if (fstat(fd, &sb)) T_THROW_EXCEPTION("TFileStats", "fstat() failed to get file's stats", true, 0xCE0001F5, close(fd); )
	lint size = sb.st_size;
	T_CLASS(TConsole, print)(kOutput, "File size: %ld bytes\n", size);
	threads_start(size, fd);
	close(fd);
}
void menu_process(TMessage file_name)
{
	TString file_path = T_CLASS(TString, constructor)("temp/%s", file_name);
	if(TFile__exists(file_path)) process_file(file_path);
	else T_THROW_EXCEPTION("Process", "File does not exists", false, 0xEF0001FE,)
	T_CLASS(TString, destructor)(file_path);
}
