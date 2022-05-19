#include "../tlinux.h"

int main(void)
{
	TSemaphore sem = T_CLASS(TSemaphore, default_constructor)("temp_sem1");		printf("%c\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, set_value)(sem, 'A');									printf("%c\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, increment)(sem);										printf("%c\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, decrement)(sem);										printf("%c\n", T_CLASS(TSemaphore, get_value)(sem));
	system("ls -l /dev/shm");
	T_CLASS(TSemaphore, destructor)(sem);
	system("ls -l /dev/shm");
	return 0;
}
