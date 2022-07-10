#define _GNU_SOURCE
#include <pthread.h>

#include "tlib.h"

typedef struct
{
	uchar red, green, blue;
} rgb_t;

typedef struct
{
	//Timer:
	TTimer timer;
	//Files:
	TString file_name;
	TFile fp, fo;
	uchar imageHeader[54];
	uchar colorTable[1024];
	TBool colorTableFlag;
	ullint imgDataSize;
	rgb_t* buffer;
	//Threads:
	uint quantity;
} Parameters;

Parameters parameters;

T_IMPORT_MEMORY_DEFINITION(rgb_t)

void rgb_start(const TBool plain)
{
	parameters.timer = T_CLASS(TTimer, default_constructor)();
	TString result = T_CLASS(TString, constructor)("res/%s", parameters.file_name);
	parameters.fp = T_CLASS(TFile, open)(result, "rb", true);   //read the file//
	T_CLASS(TString, destructor)(result);
	if (plain) result = T_CLASS(TString, constructor)("tmp/grey_plain_%s", parameters.file_name);
	else result = T_CLASS(TString, constructor)("tmp/grey_threads_%s", parameters.file_name);
	if (T_CLASS(TFile, exists)(result)) T_CLASS(TFile, remove)(result, true);
	T_CLASS(TFile, create)(result, true);
	parameters.fo = T_CLASS(TFile, open)(result, "wb", true);
	T_CLASS(TString, destructor)(result);
}

TString T_CONVERTER(TString, TBool)(const TBool flag)
{
	static TString result[] = { "false", "true" };
	return result[flag];
}

void rgb_read(void)
{
	T_CLASS(TTimer, start)(parameters.timer);
	{
		fread(parameters.imageHeader, sizeof(uchar), 54, parameters.fp); // read the 54-byte from fp to imageHeader
		// extract image height and width from imageHeader
		uint width = *(uint*)&parameters.imageHeader[18];
		uint height = *(uint*)&parameters.imageHeader[22];
		uint bitDepth = *(uint*)&parameters.imageHeader[28];
		parameters.colorTableFlag = bitDepth <= 8;
		if(parameters.colorTableFlag) fread(parameters.colorTable, sizeof(uchar), 1024, parameters.fp); // COLOR TABLE Present: read the 1024-byte from fp to colorTable
		T_CLASS(TConsole, print)(kOutput, "Image header content:\n\tW: %u,\tH: %u,\tD: %u,\tT: %s.\n", width, height, bitDepth, T_CONVERTER(TString, TBool)(parameters.colorTableFlag));
		parameters.imgDataSize = width * height;		//calculate image size
		parameters.buffer = T_MEMORY_MANAGER(rgb_t, allocate)(parameters.imgDataSize);
		for(ullint i = 0u; i < parameters.imgDataSize; ++i)
		{
			parameters.buffer[i].blue = getc(parameters.fp);
			parameters.buffer[i].green = getc(parameters.fp);
			parameters.buffer[i].red = getc(parameters.fp);
		}
	}
	T_CLASS(TTimer, stop)(parameters.timer);
	T_CLASS(TConsole, print)(kLog, "Reading is finished:\t\t%Lf ms\n", T_CLASS(TTimer, miliseconds)(parameters.timer));
}
void rgb_calc(void)
{
	T_CLASS(TTimer, start)(parameters.timer);
	{
		for(ullint i=0; i < parameters.imgDataSize;++i)
			parameters.buffer[i].red = parameters.buffer[i].green = parameters.buffer[i].blue =
					(parameters.buffer[i].red*0.299083) + (parameters.buffer[i].green*0.585841) + (parameters.buffer[i].blue*0.114076); //conversion formula of rgb to gray;
	}
	T_CLASS(TTimer, stop)(parameters.timer);
	T_CLASS(TConsole, print)(kLog, "Plain Calculations are over:\t%Lf ms\n", T_CLASS(TTimer, miliseconds)(parameters.timer));
}
void rgb_write(void)
{
	T_CLASS(TTimer, start)(parameters.timer);
	{
		fwrite(parameters.imageHeader, sizeof(uchar), 54, parameters.fo); // write the header back.
		if(parameters.colorTableFlag) fwrite(parameters.colorTable, sizeof(uchar), 1024, parameters.fo); // COLOR TABLE Present: write the color table back

		for(ullint i=0; i < parameters.imgDataSize;++i)
		{
			putc(parameters.buffer[i].blue,parameters.fo);
			putc(parameters.buffer[i].green,parameters.fo);
			putc(parameters.buffer[i].red,parameters.fo);
		}
	}
	T_CLASS(TTimer, stop)(parameters.timer);
	T_CLASS(TConsole, print)(kLog, "Writing is finished:\t\t%Lf ms\n", T_CLASS(TTimer, miliseconds)(parameters.timer));
}
void rgb_end(void)
{
	T_MEMORY_MANAGER(rgb_t, deallocate)(parameters.buffer);
	fclose(parameters.fo);
	fclose(parameters.fp);
}

T_IMPORT_MEMORY_DEFINITION(pthread_t)

#define BLCK (parameters.imgDataSize / parameters.quantity)

void* rgb_greyshale(void *tid)
{
	for(ullint i = (ullint)tid * BLCK; i < parameters.imgDataSize && i < ((ullint)tid + 1) * BLCK; ++i)
		parameters.buffer[i].red = parameters.buffer[i].green = parameters.buffer[i].blue =
				(parameters.buffer[i].red*0.299083) + (parameters.buffer[i].green*0.585841) + (parameters.buffer[i].blue*0.114076); //conversion formula of rgb to gray;
	//T_CLASS(TConsole, print)(kLog, "Thread No.%Lu finished\n", pthread_self());
	sched_yield();
	pthread_exit(nullptr);
	return nullptr;
}

void rgb_thread_calc(void)
{
	T_CLASS(TTimer, start)(parameters.timer);
	{
		pthread_t* threads = T_MEMORY_MANAGER(pthread_t, allocate)(parameters.quantity);
		for (ullint i = 0u; i < parameters.quantity; ++i)
		{
			// thread's id, default attributes, procedure
			int status = pthread_create(&threads[i], nullptr, rgb_greyshale, (void *)i);
			//T_CLASS(TConsole, print)(kLog, "Creating thread No %Lu (%Lu)...\n", i, threads[i]);
			if (status != 0)
			{
				T_MEMORY_MANAGER(pthread_t, deallocate)(threads);
				T_THROW_EXCEPTION("Threads", "Function 'pthread_create' failed to create a new thread correctly", true, 0xCE0001C1, return;)
			}
		}
		for (ullint i = 0u; i < parameters.quantity; ++i)
		   pthread_join(threads[i], nullptr);
		T_MEMORY_MANAGER(pthread_t, deallocate)(threads);
	}
	T_CLASS(TTimer, stop)(parameters.timer);
	T_CLASS(TConsole, print)(kLog, "Thread Calculations are over:\t%Lf ms\n", T_CLASS(TTimer, miliseconds)(parameters.timer));
}

int main(void)
{
	parameters.quantity = 1u;
	while (true)
	{
		T_FUNCTION(syscall, clear)();
		T_CLASS(TConsole, print)(kOutput, "Available images:\n");
		system("ls res -1 && echo "" && ls tmp -1");
		T_CLASS(TConsole, print)(kOutput, "Type 'q' to quit\nType 's' to set number of threads\nCurrent number of threads: %d\n", parameters.quantity);
		T_CLASS(TString, destructor)(parameters.file_name);
		parameters.file_name = T_CLASS(TConsole, getline)("file name", false);
		if (T_CLASS(TString, equal)(parameters.file_name, "q")) break;
		if (T_CLASS(TString, equal)(parameters.file_name, "s"))
		{
			TString quantity = T_CLASS(TString, default_constructor)();
			while (true)
			{
				T_CLASS(TString, destructor)(quantity);
				quantity = T_CLASS(TConsole, getline)("new threads quantity", false);
				T_CLASS(TString, parser)(quantity, "%zu", &parameters.quantity);
				if (parameters.quantity > PTHREAD_THREADS_MAX) T_CLASS(TConsole, print)(kError, "Quantity must be smaller than %Lu!\n", PTHREAD_THREADS_MAX);
				else if (parameters.quantity != 0) break;
				else T_CLASS(TConsole, print)(kError, "Quantity must be diffrent from zero!\n");
			}
			T_CLASS(TString, destructor)(quantity);
		}
		else
		{
			TString result = T_CLASS(TString, constructor)("res/%s", parameters.file_name);
			if (!T_CLASS(TFile, exists)(result)) T_CLASS(TConsole, print)(kError, "There is no file with the name you provided!\n");
			else for (TBool plain_mode = true; true; plain_mode = false)
			{
				rgb_start(plain_mode);
				rgb_read();
				(plain_mode ? rgb_calc : rgb_thread_calc)();
				rgb_write();
				rgb_end();
				if (plain_mode == false) break;
			}
			T_CLASS(TString, destructor)(result);
		}
		T_FUNCTION(syscall, pause)();
	}
	T_CLASS(TString, destructor)(parameters.file_name);
	return 0;
}
