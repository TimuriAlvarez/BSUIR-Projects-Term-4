#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#include "circle.h"

int leave_process = 0;

// "123\0" -> 123, returns value
int CharToInt(char *line){
	int result = 0, runner = 0, neg_flag = 0;
	while(line[runner] != '\0'){
		if(line[runner] == '-'){
			neg_flag = 1;
			runner++;
			continue;
		}
		result = result * 10 + line[runner]-48;
		runner++;
	}
	if(neg_flag != 0)
		result*=-1;
	return result;
}

void killer_proc(int sig){
	if (sig == SIGUSR1) leave_process = 1;
}

void Read(struct Circle **BufferCircle){
	unsigned long long check_checksum = 0;
	for(int i = 0; (*BufferCircle)->message[i] != '\0';i++)
	{
		int num = (*BufferCircle)->message[i];
		check_checksum = check_checksum + num*i;
	}
	if(check_checksum != (*BufferCircle)->checksum)
		T_CLASS(TConsole, print)(kError, "Checksum wasnt correct!\n");
	T_CLASS(TConsole, print)(kInput, "Taker %d read: %s\n", getpid(), (*BufferCircle)->message);
	for(int i = 0; i < 254;i++)
		(*BufferCircle)->message[i] = '\0';
	(*BufferCircle)->checksum = 0;
	(*BufferCircle)->deleted++;
}

int main(__attribute__((unused))int argc, char *argv[]){
	sem_t *SemProducer = sem_open("/semproducer", 0664,0);
	sem_t *SemTaker = sem_open("/semtaker", 0664,0);
	sem_t *SemMutex = sem_open("/semmutex", 0664,1);

	if(SemProducer == SEM_FAILED || SemTaker == SEM_FAILED || SemMutex == SEM_FAILED ||
	   SemProducer == nullptr || SemTaker == nullptr || SemMutex == nullptr)
		T_THROW_EXCEPTION("Semaphore", "Function sem_open(...) failed to create a semaphore",true,0xCE000150, return -1; );

	struct sigaction killer;
	killer.sa_handler = killer_proc;
	sigaction(SIGUSR1,&killer,0);

	struct Circle *BufferCircle = shmat(CharToInt(argv[0]),nullptr,0); int set_shmid;


	while(leave_process == 0){
		sem_wait(SemTaker);

		sem_wait(SemMutex);
		if(BufferCircle->message[0] != '\0')
		{
			Read(&BufferCircle);
			sem_post(SemMutex);
			sem_post(SemTaker);
			sleep(3);
		} else
		{
			sem_post(SemMutex);
			sem_post(SemTaker);
		}

		//going to right circle
		set_shmid = BufferCircle->right_shmid;
		shmdt(BufferCircle);
		shmat(set_shmid,nullptr,0);
		sleep(1);
	}

	shmdt(BufferCircle);

	sem_close(SemMutex);
	sem_close(SemProducer);
	sem_close(SemTaker);

	return 0;
}
