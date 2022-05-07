#include "../tlinux.h"

int main(void)
{
	TSemaphore sem = T_CLASS(TSemaphore, default_constructor)("temp_sem");		printf("%u\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, set_value)(sem, 'A');									printf("%u\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, increment)(sem);										printf("%u\n", T_CLASS(TSemaphore, get_value)(sem));
	T_CLASS(TSemaphore, decrement)(sem);										printf("%u\n", T_CLASS(TSemaphore, get_value)(sem));
	system("ls -l /dev/shm");
	system("zsh");
	T_CLASS(TSemaphore, destructor)(sem);
	return 0;
}
