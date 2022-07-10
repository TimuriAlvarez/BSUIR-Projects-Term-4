#include <ctype.h>
#include <sys/mman.h>
#include <unistd.h>

#include "tthread.h"

#define CONTAINER_DATA_TYPE TThread
#include "../../../TContainersC/timport/tvector.c"

extern llint quantity;

TString file;
T_CONTAINER(TVector, TThread, T_CONTAINER_POSTFIX) threads;

void threads_end(void)
{
	FOR_EACH_ITERATOR_FROM(thread_ptr, TVector, TThread, threads)
		pthread_join(*thread_ptr, nullptr);
	T_CONTAINER(TVector, TThread, clear)(threads);
}

typedef struct
{
	ssize_t n_start, n_end;
} ThreadStructure;
T_IMPORT_MEMORY_DEFINITION(ThreadStructure)

TPointer thread_sycle(TPointer pointer)
{
	ThreadStructure* structure = pointer;
	for (ssize_t index = structure->n_start; index < structure->n_end - 1; ++index)
		if (file[index] == ' ') file[index] = '_';
		elif (file[index] == '_') file[index] = ' ';
		elif (rand() % 2) file[index] = toupper(file[index]);
		else file[index] = tolower(file[index]);
	sched_yield();
	pthread_exit(T_MEMORY_MANAGER(ThreadStructure, deallocate)(structure));
}

void add_thread(ssize_t n_start, ssize_t n_end)
{
	TThread thread;
	ThreadStructure* structure = T_MEMORY_MANAGER(ThreadStructure, allocate)(1);
	structure->n_start = n_start;
	structure->n_end = n_end;
	int status = pthread_create(&thread, nullptr, thread_sycle, structure);
	if (status == 0) T_RETURN_VOID(T_CONTAINER(TVector, TThread, append)(threads, thread, true);)
	T_THROW_EXCEPTION("Threads", "Function 'pthread_create' failed to create a new thread correctly", false, 0xCE00011E, T_RETURN_VOID(threads_end();))
}

void threads_start(const lint size, const TFileDescriptor fd)
{
	threads = T_CONTAINER(TVector, TThread, default_constructor)();
	ssize_t page_sz = sysconf(_SC_PAGESIZE) * 10;
	ssize_t blck_qn = size / page_sz;
	if (size % page_sz) ++blck_qn;
	ssize_t thrd_sz = page_sz / quantity;
	if (page_sz % quantity) ++thrd_sz;
	for (ssize_t k = 0u; k < blck_qn; ++k)
	{
		ssize_t k_start = k * page_sz, k_end = k_start + page_sz;
		if (k_end > size) k_end = size;
		T_CLASS(TConsole, print)(kOutput, "%5lu - %5lu:\n", k_start, k_end);
		file = mmap(nullptr, page_sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, k * page_sz);
		if(file == MAP_FAILED) T_THROW_EXCEPTION("MMap", "Function 'mmap()' failed to map a file", false, 0xCE000100, T_RETURN_VOID(threads_end();))
		for (llint n = 0u; n < quantity; ++n)
		{
			ssize_t n_start = n * thrd_sz, n_end = n_start + thrd_sz;
			if (k_start + n_start > k_end) break;
			if (k_start + n_end > k_end) n_end = k_end - k_start;
			add_thread(n_start, n_end);
		}
		threads_end();
		munmap(file, page_sz);
	}
	T_CONTAINER(TVector, TThread, destructor)(threads);
	T_CLASS(TConsole, print)(kLog, "Finished.\n");
}
