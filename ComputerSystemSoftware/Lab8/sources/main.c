#include "tlib.h"
#include <unistd.h>

T_CONTAINER(TVector, pthread_t, Container) threads;
T_CONTAINER(TVector, uint, Container) signals;

typedef struct
{
	int a, b;
} ThreadStruct;
typedef struct
{
	size_t iteration;
	TBool is_allowed_printing;
	size_t zz, zo, oz, oo;
} ThreadStats;

pthread_mutex_t lock;
void print_structure_stats(ThreadStats stats)
{
	pthread_mutex_lock(&lock);
	T_CLASS(TConsole, print)(kLog, "tid: %lu; ", pthread_self());
	T_CLASS(TConsole, print)(kLog, "'00': %zu\t\t'01': %zu\t\t", stats.zz, stats.zo);
	T_CLASS(TConsole, print)(kLog, "'10': %zu\t\t'11': %zu.\n", stats.oz, stats.oo);
	pthread_mutex_unlock(&lock);
}

void gather_stats(ThreadStruct* const structure, ThreadStats* const stats)
{
	if (structure->a ==0)
	{
		if (structure->b ==0) ++stats->zz;
		else ++stats->zo;
	}
	else
	{
		if (structure->b ==0) ++stats->oz;
		else ++stats->oo;
	}
}

void* thread_sycle(void* pointer)
{
	static const size_t kCycle = 10000u;
    static const size_t kProbability = 80u;
	ThreadStruct structure =  { 0, 0 };
	ThreadStats stats = { 0, false, 0, 0, 0, 0 };
	size_t index = (size_t)pointer;
	while (true) switch ((ThreadAction)(*T_CONTAINER(TVector, uint, at_index)(signals, index)))
	{
	case kNoAction:
		srand(time(nullptr));
		sleep(0); structure.a = 0; if (rand() % kProbability == 0) gather_stats(&structure, &stats);
		sleep(0); structure.b = 0; if (rand() % kProbability == 0) gather_stats(&structure, &stats);
		sleep(0); structure.a = 1; if (rand() % kProbability == 0) gather_stats(&structure, &stats);
		sleep(0); structure.b = 1; if (rand() % kProbability == 0) gather_stats(&structure, &stats);
		++stats.iteration;
		if (stats.iteration % kCycle == 0 && stats.is_allowed_printing)
			*T_CONTAINER(TVector, uint, at_index)(signals, index) = kPrintThread;
		break;
	case kMuteThread:
		stats.is_allowed_printing = false;
		*T_CONTAINER(TVector, uint, at_index)(signals, index) = kNoAction;
		break;
	case kUnmuteThread:
		stats.is_allowed_printing = true;
		*T_CONTAINER(TVector, uint, at_index)(signals, index) = kNoAction;
		break;
	case kPrintThread:
		print_structure_stats(stats);
		*T_CONTAINER(TVector, uint, at_index)(signals, index) = kNoAction;
		break;
	case kKillThread:
		sched_yield();
		pthread_exit(nullptr);
	case kGatherStats:
		gather_stats(&structure, &stats);
		break;
	}
}

void kill_all(void)
{
	FOR_EACH_ITERATOR_FROM(iterator, TVector, uint, signals) *iterator = kKillThread;
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pthread_t, threads) pthread_join(*iterator, nullptr);
	T_CONTAINER(TVector, pthread_t, clear)(threads);
	T_CONTAINER(TVector, uint, clear)(signals);
}

static const size_t FAILED = (size_t)(-1);

size_t find_tid(T_CONTAINER(TVector, pthread_t, Container) const container, const pthread_t tid)
{
	size_t index = 0u;
	FOR_EACH_ITERATOR_FROM(iterator, TVector, pthread_t, container)
	{
		if (*iterator == tid)
			return index;
		++index;
	}
    T_CLASS(TConsole, print)(kError, "There is no thread with provided tid!\n");
	return FAILED;
}

size_t get_index(TMessage message)
{
	char temp_char = '\0';
	llint thread_id = 0u;
	T_CLASS(TString, parser)(message, "%c %lld", &temp_char, &thread_id);
	if (thread_id >= 0) return find_tid(threads, thread_id);
	/* else */
	thread_id *= -1;
	if ((size_t)thread_id > T_CONTAINER(TVector, pthread_t, size)(threads))
	{
		T_CLASS(TConsole, print)(kError, "Provided index is out of range!\n");
		return FAILED;
	}
	return thread_id - 1;
}

int main0(void)
{
	TString string = T_CLASS(TString, default_constructor)();
	threads = T_CONTAINER(TVector, pthread_t, default_constructor)();
	signals = T_CONTAINER(TVector, uint, default_constructor)();
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
        printf("\n mutex init has failed to initialize\n");
		return 1;
	}

	while (true)
	{
        T_FUNCTION(syscall, clear)();
		top_bar(threads);
		T_CLASS(TConsole, print)(kOutput, "> ");
		T_CLASS(TString, destructor)(string);
		pthread_mutex_lock(&lock);
		string = T_CLASS(TConsole, getline)(nullptr, true);
		pthread_mutex_unlock(&lock);
		//	Empty string
		if (T_CLASS(TString, empty)(string))
		{
			T_FUNCTION(syscall, clear)();
			continue;
		}
		//	Quit the programm
		if (T_CLASS(TString, equal)(string, "q"))
		{
			kill_all();
			threads = T_CONTAINER(TVector, pthread_t, destructor)(threads);
			signals = T_CONTAINER(TVector, uint, destructor)(signals);
			pthread_mutex_destroy(&lock);
			return 0;
		}
		//	Add a thread
		if (T_CLASS(TString, equal)(string, "+"))
		{
			pthread_t thread;
			T_CONTAINER(TVector, uint, append)(signals, kNoAction, true);
			int status = pthread_create(&thread, nullptr, thread_sycle, (void*)T_CONTAINER(TVector, pthread_t, size)(threads));
			if (status != 0)
			{
				kill_all();
				T_THROW_EXCEPTION("Threads", "Function 'pthread_create' failed to create a new thread correctly", true, 0xCE00011E, return -1;)
			}
			T_CONTAINER(TVector, pthread_t, append)(threads, thread, true);
		}
		else if (!vector_is_empty(threads))
		{
			//	Kill the last thread
			if (T_CLASS(TString, equal)(string, "-"))
			{
				*T_CONTAINER(TVector, uint, at_index)(signals, (T_CONTAINER(TVector, uint, size)(signals) - 1u)) = kKillThread;
				pthread_join(*T_CONTAINER(TVector, pthread_t, at_index)(threads, T_CONTAINER(TVector, pthread_t, size)(threads) - 1u), nullptr);
				T_CONTAINER(TVector, uint, chop)(signals, true);
				T_CONTAINER(TVector, pthread_t, chop)(threads, true);
			}
			//	Kill all threads
			else if (T_CLASS(TString, equal)(string, "k")) kill_all();
			//	Mute all threads
			else if (T_CLASS(TString, equal)(string, "m")) FOR_EACH_ITERATOR_FROM(iterator, TVector, uint, signals) *iterator = kMuteThread;
			//	Unmute all threads
			else if (T_CLASS(TString, equal)(string, "u")) FOR_EACH_ITERATOR_FROM(iterator, TVector, uint, signals) *iterator = kUnmuteThread;
			//	Print stats for all threads
			else if (T_CLASS(TString, equal)(string, "p"))
			{
				FOR_EACH_ITERATOR_FROM(iterator, TVector, uint, signals) *iterator = kPrintThread;
				sleep(1);
			}
			else if (string[1u] == ' ')
			{
				size_t index = get_index(string);
                if (index == FAILED)
                {
                    T_FUNCTION(syscall, pause)();
                    continue;
                }
				switch (string[0u])
				{
				case 'm':
					*T_CONTAINER(TVector, uint, at_index)(signals, index) = kMuteThread;
					break;
				case 'u':
					*T_CONTAINER(TVector, uint, at_index)(signals, index) = kUnmuteThread;
					break;
				case 'p':
					*T_CONTAINER(TVector, uint, at_index)(signals, index) = kPrintThread;
					break;
				default:
					T_CLASS(TConsole, print)(kError, "Invalid command!\n");
					break;
				}
			}
			else T_CLASS(TConsole, print)(kError, "Invalid command!\n");
		}
        T_FUNCTION(syscall, pause)();
	}
}

int main(void)
{
	TTimer timer = T_CLASS(TTimer, default_constructor)();
	sleep(0);
	T_CLASS(TConsole, print)(kOutput, "%Lf\n", T_CLASS(TTimer, miliseconds)(timer));
	T_CLASS(TTimer, destructor)(timer);
}
