#include <stdio.h>
#include <semaphore.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#include <sys/stat.h>
#ifdef __linux__
#include <sys/wait.h>
#endif

#include "circle.h"

// 123 -> "123\0"
char* IntToChar(int num){
	char *line = (char*)malloc(sizeof(char)); int size = 0;
	int rev_x = 0;
	if(num < 0){
		line[0] = '-';
		line = (char*)realloc(line,2*sizeof(char));
		size++; rev_x++;
	}
	while(num != 0){
		char temp = num%10+48;
		num/=10;
		line[size] = temp;
		size++;
		line = (char*)realloc(line,(size+2)*sizeof(char));
	}
	line[size] = '\0';
	size--;
	for(;rev_x < size;rev_x++,size--){
		char temp = line[rev_x];
		line[rev_x] = line[size];
		line[size] = temp;
	}
	return line;
}

//creates new array of pids that larger by one than old and returns it
int* UpdatePidsIncrease(int **old_pids, int count)
{
	int* new_pids;
	new_pids = (int*)malloc(count*sizeof(int));
	for(int i = 0; i < count-1; i++)
		new_pids[i] = (*old_pids)[i];
	free((*old_pids));
	return new_pids;
}

//creates new arrey of pids that lower by one than old, kills the newest pid and returns array
int* UpdatePidsDecrease(int **old_pids, int count)
{
	int* new_pids, temp;
	new_pids = count == 0 ? nullptr : (int*)malloc(count*sizeof(int));
	temp = kill((*old_pids)[count],SIGUSR1);
	if(temp != 0)
		T_CLASS(TConsole, print)(kError, "Error killing procces! Try to exit program to prevent proccess stuck in system\n");
	else
	{
		waitpid((*old_pids)[count], nullptr, 0);       //to avoid proccess become a zombie we ask parent to close it
		T_CLASS(TConsole, print)(kLog, "%d - procces was killed\n", (*old_pids)[count]);
	}
	if (new_pids != nullptr) for(int i = 0; i < count; i++)
		new_pids[i] = (*old_pids)[i];
	free((*old_pids));
	return new_pids;
}

int main(void)
{
	T_CLASS(TConsole, default_constructor)();
	T_CLASS(TConsole, debug)(true);
	struct Circle *BufferCircle = nullptr;

	sem_unlink("/semproducer");
	sem_unlink("/semtaker");
	sem_unlink("/semmutex");

	sem_t* SemProducer = sem_open("/semproducer", O_CREAT, 0644,0);
	sem_t* SemTaker = sem_open("/semtaker", O_CREAT, 0644, 0);
	sem_t* SemMutex = sem_open("/semmutex", O_CREAT, 0644, 1);

	if(SemProducer == SEM_FAILED || SemTaker == SEM_FAILED || SemMutex == SEM_FAILED)
		T_THROW_EXCEPTION("Semaphore", "Function sem_open(...) failed to create a semaphore",E_LOCATION,true,0xCE000150,0xCE000150);

	//DATA SEG
	int *ProducerPids, CountProducer=0, CreatedCircles = 0;
	int *TakerPids, CountTaker=0;
	ProducerPids = (int*)malloc(sizeof(int));
	TakerPids = (int*)malloc(sizeof(int));
	char *get_line = T_CLASS(TString, default_constructor)();
	int leave = 1;

	//END DATA SEG

	while(leave)
	{
		system("clear");
		T_CLASS(TConsole, print)(kOutput, "Menu options:\n"
							 "\t c)\tcreate shared memory\n"
							 "\t s)\tshow statistic for shared memory\n"
							 "\t p)\tcreate one more producer\n"
							 "\t t)\tcreate one more taker\n"
							 "\t-p)\tdelete last created producer\n"
							 "\t-t)\tdelete last created taker\n"
							 "\t q)\tquit programm\n"
							 "Choose the option: ");
		T_CLASS(TString, destructor)(get_line);
		get_line = T_CLASS(TConsole, getline)(nullptr, true);
		if (T_CLASS(TString, empty)(get_line)) continue;
		switch(get_line[0])
		{
			case 'p':
			{
				if(BufferCircle == nullptr)
				{
					T_CLASS(TConsole, print)(kError, "Cant create producer/taker without having any slots of memory\n");
					break;
				}
				int temp = fork();  //creating proccess
				if(temp == -1)
				{    //check if we actually creat him
					T_CLASS(TConsole, print)(kError, "Error while creating proccess!\n");
					break;
				}
				if (temp != 0)
				{ //for parent: updating info about pids
					CountProducer++;
					ProducerPids = UpdatePidsIncrease(&ProducerPids, CountProducer);
					ProducerPids[CountProducer-1] = temp;
					T_CLASS(TConsole, print)(kLog, "%d - Producer procces was created\n",ProducerPids[CountProducer-1]);
					sem_post(SemProducer);
				}
				else
				{
					char *send_shmid = IntToChar(BufferCircle->current_shmid);
					execl("bin/producer",send_shmid, nullptr);
					free(send_shmid);
					T_CLASS(TConsole, print)(kError, "Critical\n");
				}
							break;
			}
			case 't':
			{
						if(BufferCircle == nullptr)
						{
							T_CLASS(TConsole, print)(kError, "Cant create producer/taker without having any slots of memory\n");
							break;
						}
						int temp = fork();  //creating proccess
						if(temp == -1)
						{    //check if we actually creat him
							T_CLASS(TConsole, print)(kError, "Error creating proccess!\n");
							break;
						}
						if (temp != 0)
						{ //for parent: updating info about pids
							CountTaker++;
							TakerPids = UpdatePidsIncrease(&TakerPids, CountTaker);
							TakerPids[CountTaker-1] = temp;
							T_CLASS(TConsole, print)(kLog, "%d - Taker procces was created\n",TakerPids[CountTaker-1]);
							sem_post(SemTaker);
						}
						else
						{
							char* send_shmid = IntToChar(BufferCircle->current_shmid);
							execl("bin/taker",send_shmid, nullptr);
							T_CLASS(TConsole, print)(kError, "Critical\n");
						}
						break;
			}
			case '-':
			{
				if(get_line[1] == 'p')
				{
					if (CountProducer == 0)
					{
						T_CLASS(TConsole, print)(kError, "There is no producers!\n");
						break;
					}
					CountProducer--;
					ProducerPids = UpdatePidsDecrease(&ProducerPids,CountProducer);
					sem_wait(SemProducer);
				} else if (get_line[1] == 't')
				{
					if (CountTaker == 0)
					{
						T_CLASS(TConsole, print)(kError, "There is no takers!\n");
						break;
					}
					CountTaker--;
					TakerPids = UpdatePidsDecrease(&TakerPids,CountTaker);
					sem_wait(SemTaker);
				}
				break;
			}
			case 'c':
			{
				sem_wait(SemMutex);
				AppendCircle(&BufferCircle);
				CreatedCircles++;
				sem_post(SemMutex);
				T_CLASS(TConsole, print)(kLog, "Circle added\n"); break;
			}
			case 'q': leave = 0; break;
			case 's':
			{
				if(CreatedCircles == 0 || BufferCircle == nullptr)
				{
					T_CLASS(TConsole, print)(kError, "There is no slots of memory\n");
					break;
				}
				T_CLASS(TConsole, print)(kOutput, "Requesting the access, wait please...\n");
				sem_wait(SemMutex);
				if (BufferCircle == nullptr) break;
				int remember_shmid = BufferCircle->current_shmid; //this will be our flag for end
				int next_shmid = BufferCircle->right_shmid;   //setting current pos
				shmdt(BufferCircle);                          //detachins block of memory
				BufferCircle = shmat(next_shmid, nullptr,0);     //setting next
				T_CLASS(TConsole, print)(kDebug, "------------------------------------------------------\n");
				while(remember_shmid != BufferCircle->current_shmid)
				{
					T_CLASS(TConsole, print)(kDebug, "SHMID:\t\t%d\nAdded:\t\t%d\nRemoved:\t%d\nCheksum:\t%lld\n",BufferCircle->current_shmid,BufferCircle->added,BufferCircle->deleted,BufferCircle->checksum);
					T_CLASS(TConsole, print)(kDebug, "------------------------------------------------------\n");
					next_shmid = BufferCircle->right_shmid;
					shmdt(BufferCircle);
					BufferCircle = shmat(next_shmid,nullptr,0);
				}
				sem_post(SemMutex);
				break;
			}
			default:
				break;
		}
		T_FUNCTION(syscall, pause)();
	}

	//END SECTION
		//killing proccess
	while(CountProducer != 0){
		CountProducer--;
		ProducerPids = UpdatePidsDecrease(&ProducerPids,CountProducer);
	}
	free(ProducerPids);
	while(CountTaker != 0){
		CountTaker--;
		TakerPids = UpdatePidsDecrease(&TakerPids,CountTaker);
	}
	free(TakerPids);
		//CLOSING SEMAPHORS
	sem_close(SemMutex);
	sem_close(SemProducer);
	sem_close(SemTaker);
	sem_unlink("/semproducer");
	sem_unlink("/semtaker");
	sem_unlink("/semmutex");
		//CLOSING SHARED MEMORY (if needed)
	if(BufferCircle == nullptr)
		return 0;
	int result_end = 1;
		//find size of circle
	int next_shmid = BufferCircle->current_shmid;
	while(result_end >= 0 && CreatedCircles != 0){
		int shmid = next_shmid;
		if(CreatedCircles > 1)
			next_shmid = BufferCircle->right_shmid;
		result_end = shmdt(BufferCircle);
		if(result_end == -1)
		{
			T_CLASS(TConsole, print)(kError, "shmdt error\n");
		}
		result_end = shmctl(shmid, IPC_RMID,nullptr);
		if(result_end == -1){
			T_CLASS(TConsole, print)(kError, "shmctl error\n");
		}
		CreatedCircles--;
		if(CreatedCircles > 0)
			BufferCircle = shmat(next_shmid,nullptr,0);
	}

	return 0;
}
